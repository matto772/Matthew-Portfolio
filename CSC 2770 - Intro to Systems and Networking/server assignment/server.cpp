//Matthew Ogurkis
//Server.cpp
//Date Started: 4/20/23
//Date Completed: 4/26/23
//NOTE: The server DOES output but you must press enter a few times for it to do so, at this moment in time I have not figured out why this occured. Thank you for your considerations
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <map>
#include <stdexcept>
#define PORT 8007
//prototypes
void  ASErrorHandler(int errorNumber, const char* errorMessage);
char*  ASMemoryAlloc(unsigned long memoryNeeded);
extern "C" char*  AStyleMain(const char* sourceIn,
                                    const char* optionsIn,
                                    void (* fpError)(int, const char*),
                                    char* (* fpAlloc)(unsigned long));
void handle_connect(int ns);
void parse(FILE *fp, std::map<std::string,std::string> &options,std::string &doc);

//global variables
bool Req_Error;
std::string Req_Estr;


int main(int argc, char* argv[]) 
{
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in cli_addr, serv_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        throw std::runtime_error("Couldn't make a socket");
    }
    bzero((void *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    { 
        throw std::runtime_error("Couldn't bind socket");
    }
    listen(sockfd, 5);
    for (;;) 
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
        { 
            throw std::runtime_error("");
        }
    handle_connect(newsockfd);
    }
}


void parse(FILE *fp, std::map<std::string, std::string> &options, std::string &doc) 
{
	// read (fgets) the first line from fp into head, trim the newline
	char head[1024];
	if (fgets(head, sizeof(head), fp) == NULL) {
		throw std::runtime_error("Unexpected end of file when reading header");
	}
	head[strcspn(head, "\r\n")] = '\0'; // trim the newline

    //making sure the header is ASTYLE, if not throw a runtime erro
	if (strcmp(head, "ASTYLE") != 0) 
    {
		throw std::runtime_error("Expected header ASTYLE, but got " + std::string(head));
	}

	int size = -1;
	char line[1024];
    //goes through each line presented too the program 
	while (fgets(line, sizeof(line), fp) != NULL) 
    {
		line[strcspn(line, "\r\n")] = '\0'; // trim the newline
		//if line is a newline then break
        if (strlen(line) == 0) 
        {
			break;
		}
		char* equals_pos = strchr(line, '='); //variable to keep the position of every = sign
		//if there is no =, throw an error: "Bad option"
        if (equals_pos == NULL) 
        {
			throw std::runtime_error("Bad option");
		}
		*equals_pos = '\0';
		   
        std::string key = line;
		std::string value = equals_pos + 1;
		
        //makes sure the key is SIZE, mode, or style, if not, throw an error
        if (key != "SIZE" && key != "mode" && key != "style") 
        {
			throw std::runtime_error("Bad option");
		}
		if (key == "SIZE") 
        {
			size = std::stoi(value);
		}
		options.insert(std::make_pair(key, value));
	}
    //size checks
	if (size < 0) 
    {
		throw std::runtime_error("Bad code size");
	}
	if (size > 1024) 
    {
		throw std::runtime_error("Bad code size");
	}

    //reading the bytes into the doc
	char buffer[1024];
	int bytes_read = 0;
	while (bytes_read < size) 
    {
		int bytes = fread(buffer + bytes_read, 1, size - bytes_read, fp);
		if (bytes == 0) 
        {
			throw std::runtime_error("Unexpected end of file when reading code");
		}
		bytes_read += bytes;
	}
	doc = std::string(buffer, size);
}


//handle connect here
void handle_connect(int ns) 
{
    // parameters: ns - data socket
    FILE* fp = fdopen(ns, "r+");
    if (!fp) 
    {
        throw std::runtime_error("fdopen failed");
    }

    // Note: header and doc are of type string
    //       options is a map of string to string
    std::string doc;
    std::map<std::string, std::string> options;
    
    //calling the parse function
    parse(fp, options, doc);
    
    //innitializing and setting up string parameter to send the astylemain
    std::string parameter;
    for (const auto& [key, value] : options) 
    {
        if (key != "SIZE") 
        {
            parameter += key + "=" + value + "\n";
        }
    }

    //calling the astyle library
    char* textOut = AStyleMain(doc.c_str(), parameter.c_str(), ASErrorHandler, ASMemoryAlloc);
    if (Req_Error) 
    {
        std::string err_msg = "ERR\nSIZE=" + std::to_string(Req_Estr.size()) + "\n\n" + Req_Estr.c_str();
        fprintf(fp, "%s", err_msg.c_str());
    } 
    else 
    {
        std::string ret_message = "OK\nSIZE=" + std::to_string(strlen(textOut)) + "\n\n" + textOut;
        fprintf(fp, "%s", ret_message.c_str());
    }

    fclose(fp);
}


void ASErrorHandler(int errorNumber, const char* errorMessage) {   
    //std::cout << "astyle error " << errorNumber << "\n"
    //     << errorMessage << std::endl;
    Req_Error = true;
    Req_Estr += errorMessage + std::string("\n");

}

char* ASMemoryAlloc(unsigned long memoryNeeded) {   // error condition is checked after return from AStyleMain
    char* buffer = new (std::nothrow) char [memoryNeeded];
    return buffer;
}


