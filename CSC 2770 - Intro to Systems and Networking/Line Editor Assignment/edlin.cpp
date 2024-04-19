//Name: Matthew Ogurkis
//Date started: 3/30/23
//Date completed: 4/9/23
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <regex>

//function prototype
void filter(std::vector<std::string> &lines, const std::string &user_cmd);

int main() 
{
  //string vector to hold the lines
  std::vector<std::string> lines;

  //greeting
  std::cout << "Line editor\n";
  std::cout << "edlin> ";
  //holds the command
  std::string command;
  
  while (std::getline(std::cin, command)) 
  {
    //command.erase(0, command.find_first_not_of(" \t"));  // trim leading whitespace
    //command.erase(command.find_last_not_of(" \t") + 1);  // trim trailing whitespace

    //if command is q, quit
    if (command == "q") 
    {
      std::cout << "Exiting the editor\n";
      break;
    } 
    //else if command is l, loop over the lines
    else if (command == "l") 
    {
      for (const auto& line : lines) 
      {
        std::cout << line << '\n';
      }
    } 
    //else if command is r, and something is given to read, it'll read.
    else if (command.size() >= 2 && command[0] == 'r' && command[1] == ' ') 
    {
      std::string fileName = command.substr(2);
      std::ifstream infile(fileName);
      
      //makes sure there's a file to read from
      if (!infile) 
      {
        std::cerr << "Error: could not open file " << fileName << '\n';
      } 
      else 
      {
        std::string line;
        lines.clear();
        while (std::getline(infile, line)) 
        {
          lines.push_back(line);
        }
        std::cout << "Read " << lines.size() << " lines from file " << fileName << '\n';
      }
    } 
    //else if the command is s, and something is there to write too, it'll write.
    else if (command.size() >= 2 && command[0] == 's' && command[1] == ' ') 
    {
      std::string filename = command.substr(2);
      std::ofstream outfile(filename);
      
      //makes sure there's a file to write too
      if (!outfile) 
      {
        std::cerr << "Error: could not open file " << filename << '\n';
      } 
      else 
      {
        for (const auto& line : lines) 
        {
          outfile << line << '\n';
        }
        std::cout << "Wrote " << lines.size() << " lines to file " << filename << '\n';
      }
    } 
    //else if the command is e, and a line is given, it'll append the line vector with that line (can be looped over with l)
    else if (command.size() >= 2 && command[0] == 'e' && command[1] == ' ') 
    {
      //position space
      size_t pos = command.find(' ', 2);
      
      //makes sure input is validated
      if (pos == std::string::npos) 
      {
        std::cerr << "Error: invalid input\n";
      } 
      else 
      {
        std::string lno_str = command.substr(2, pos - 2);
        std::string rest_of_line = command.substr(pos + 1);
        int lno = std::atoi(lno_str.c_str());
        if (lno < 0 || static_cast<size_t>(lno) > lines.size()) 
        {
          std::cerr << "Error: invalid line number\n";
        } 
        else 
        {
          if (static_cast<size_t>(lno) == lines.size()) 
          {
            lines.push_back(rest_of_line);
          } 
          else 
          {
            lines[lno] = rest_of_line;
          }
        }
      }
    } 
    //else if the command is ! and a command is given, filter will be called for that line
    else if (command.size() >= 2 && command[0] == '!' && command[1] == ' ') 
    {
      filter(lines, command);
    } 
    else 
    {
      std::cerr << "Error: invalid command\n";
    }

    std::cout << "edlin> ";
  }

  return 0;
}

//filter here
void filter(std::vector<std::string> &lines, const std::string &user_cmd) 
{

  int lno;
  std::string ucmd;
  
  std::string::size_type space_pos = user_cmd.find(' ');
    if (space_pos != std::string::npos && user_cmd[space_pos + 1] >= '0' && user_cmd[space_pos + 1] <= '9') 
    {
        lno = user_cmd[space_pos + 1] - '0';
        //std::cout << "Found number: " << lno << std::endl;
    } 
    else 
    {
        std::cout << "No number found in input string." << std::endl;
        return;
    }
  //parse the Unix command into a variable ucmd
    std::string::size_type cmd_start_pos = user_cmd.find_first_not_of(" \t", space_pos);
    if (cmd_start_pos != std::string::npos) 
    {
        ucmd = user_cmd.substr(cmd_start_pos);
        // Remove line number from command string
        if (ucmd[0] >= '0' && ucmd[0] <= '9') 
        {
            std::string::size_type cmd_space_pos = ucmd.find(' ');
            if (cmd_space_pos != std::string::npos) 
            {
                ucmd = ucmd.substr(cmd_space_pos + 1);
            } 
            else 
            {
                ucmd = "";
            }
        }
        //std::cout << "Found Unix command: " << ucmd << std::endl;
    } 
    else 
    {
        std::cout << "No Unix command found in input string." << std::endl;
        return;
    }
  // check for error (no line given, 
  // not a integer, and no Unix command given
  if (lno == 0 || ucmd == "") 
  {
    std::cerr << "Error: invalid input\n";
    return;
  }
  
  //create a pipe called from_parent
  int from_parent[2];
  //create a pipe called to_parent
  int to_parent[2];

  if (pipe(from_parent) == -1 || pipe(to_parent) == -1) 
  {
    perror("Error creating pipes");
    return;
  }
				
  //call fork()
  pid_t pid = fork();
  if (pid == -1) 
  {
    perror("Error forking");
    return;
  }
  
  //if I am the child
if (pid == 0) 
{
    close(from_parent[1]);
    close(to_parent[0]);  
    //call dup2 to copy read end of from_parent to stdin
    //call dup2 to copy write end of to_parent to stdout
    dup2(from_parent[0], STDIN_FILENO);
    dup2(to_parent[1], STDOUT_FILENO);
    //close read end of to_parent and write end of to_parent
    //close read end of from_parent and write end of from_parent
	  close(to_parent[0]);
    close(to_parent[1]);
    close(from_parent[0]);
    close(from_parent[1]);
   
    //create args array to run ucmd in a shell
	// the above looks like:
	//   args[0] = "/bin/sh"
	//   args[1] = "-c"
	//   args[2] = ucmd
	//   args[3] = 0
    char *args[] = { (char*)"/bin/sh",(char*)"-c", const_cast<char*>(ucmd.c_str()), nullptr};
	//call execve on args
    // make sure to check for errors, and exit(1) if so
    if (execve(args[0], args, nullptr) == -1) 
    {
      perror("execve failed");
      exit(EXIT_FAILURE);
    }
	// make sure to check for errors, and exit(1) if so
   } 
    else 
    {
        //else I am the parent
        //close read end of from_parent
        //close write end of to_parent  
        close(from_parent[0]);
        close(to_parent[1]);
        
        // Note: use fdopen and fprintf to make the
	    //       following easy
	    //write lines[lno] to write end of from_parent
	    //close write end of from_parent // or fclose the FILE *
        FILE* write_end = fdopen(from_parent[1], "w");
        fprintf(write_end, "%s", lines[lno].c_str());
        fclose(write_end);
        //close(from_parent[1]);

        // again, use fdopen with fgets to make the
	    //	following easy
	    //      fgets returns NULL (0) if nothing was read 
	    //read a line ln from the read end of to_parent
        FILE* read_end = fdopen(to_parent[0], "r");
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), read_end)) 
        {
            lines[lno] = buffer;
        }
        fclose(read_end);
        close(to_parent[0]);

        //close to_parent's read end
        //wait for child to exit
        int status;
        if(waitpid(pid, &status, 0) == -1)
        {
            waitpid(pid, &status, 0);
        }

    }

}
