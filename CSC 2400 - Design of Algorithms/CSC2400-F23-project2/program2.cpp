/*
     Title:     program2.cpp
     Author:    Matthew Ogurkis
     Date Started: 10/27/2023
     Date Complete: 11/1/2023       
     Purpose:   Traveling Salesman - find the lowest cost
                tour when traveling from US to 8 other countries
                and then back to US.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "GraphMatrix.h"
using namespace std;

const int SIZE = 10;
const string COUNTRY_CODES[SIZE]={"AU", "BR", "CA", "CN", "GL", "IT", "NA", "RU", "US", "US"};

/*
	Use the following structure to store each tour & its cost
	You will create an array of Tour variables in your program
*/
struct Tour
{
	string tour[SIZE];
	int cost;
};

//Function Prototypes
int searchCountryCode(string code);
GraphMatrix* readFileMakeMatrix();
void printStringArray(string* arr, int size);
void lexicographic(string *arr, int size, Tour *tourOptions, GraphMatrix *matrix, int left, int right, int& index);
void saveTour(Tour *tourOptions, string *arr, int size, GraphMatrix *matrix, int index);



int main() 
{
    Tour *tourOptions = new Tour[40320]; // Creating an array of Tours to store the permutations
    GraphMatrix *matrix = readFileMakeMatrix(); // Reading flight data and creating the weight matrix
    string *countries = new string[SIZE - 2];

    cout << "\n\n*************************COUNTRIES*******************\n";
    for (int x = 0; x < SIZE - 2; x++) 
	{
        countries[x] = COUNTRY_CODES[x];
        cout << countries[x] << endl;
    }

    //calling the lexicographic algorithm here
    int tourCount = 0;
    lexicographic(countries, SIZE - 2, tourOptions, matrix, 0, SIZE - 3, tourCount);

    //printing out all the tours here with the lexicographic partitioning algorithm
    cout << "\nLEXICOGRAPHIC ALGORITHM" << endl;
    for (int i = 0; i < tourCount; i++) 
    {
        cout << (i + 1) << ": ";
        for (int j = 0; j < SIZE; j++) 
        {
            cout << tourOptions[i].tour[j] << " ";
        }
        cout << " has tour weight: " << tourOptions[i].cost << endl;
    }

    //finding the lowest cost tour right here and printing each subsequent new lowest as per the output requirements
    cout << "\n\n*************************SOLUTION*******************" << endl;
    int lowestCost = INT_MAX;
    int lowestTourIndex = -1;
    //right here we will loop though the tours and check if the current touch is lower than our current lowest
    for (int i = 0; i < tourCount; i++) 
    {
        //if the current tour's cost is lower than the current lowest, make it the new lowest and print it out as so!
        if (tourOptions[i].cost < lowestCost) 
        {
            lowestCost = tourOptions[i].cost;
            lowestTourIndex = i;
            cout << "New Lowest is: " << lowestCost << " with tour ";
            for (int j = 0; j < SIZE; j++) 
            {
                cout << tourOptions[i].tour[j] << " ";
            }
        cout << endl;
        }
    }

    //final printout here with the lowest cost tour as well as the "happy traveling!" as seen in the example output
    cout << "\n\n****************************************************" << std::endl;
    if (lowestTourIndex != -1) 
    {
        cout << "The tour with the lowest cost of $" << lowestCost << " is: ";
        printStringArray(tourOptions[lowestTourIndex].tour, SIZE);
    }
    cout << "\nHappy Traveling!" << endl;


    delete[] countries;
    delete[] tourOptions;
    delete matrix;

    return 0;
}


/*
	Function: searchCountryCode
	Parameters: a string with the country code like "BR"
	Returns: an integer representing this country's index in the GraphMatrix.
	For example, if the parameter is "BR", it should return index 1.  If the parameter is "CA", it should return index 3
	It is returning the index value in the COUNTRY_CODES array.	
	Implement this search function with the binary search algorithm!
*/
int searchCountryCode(string code)
{
	for (int i = 0; i < SIZE; i++) 
	{
		if (COUNTRY_CODES[i] == code) 
		{
			return i;
		}
	}
	return -1;
}

/*
	Title: readFileMakeMatrix
	Purpose:  this function will read the data in flights.txt and create an
	adjacency matrix with the couuntry codes.  The matrix values will be the
	cost of the flights.
*/
GraphMatrix* readFileMakeMatrix()
{
	ifstream inFile;
	GraphMatrix * matrix = new GraphMatrix(SIZE-1);
	cout << "\nCreated the matrix.";
	string country1, country2;
	int price;
	inFile.open("flights.txt");
	cout << "\nReading from flights.txt\n";
	if(inFile)
	{
		while(inFile >> country1)
		{
			inFile >> country2;
			inFile >> price;
			//add price to graph matrix
			matrix->addEdge(searchCountryCode(country1), searchCountryCode(country2), price);
			cout << "\nAdded edge from " << country1 << " to " << country2 << " with cost of $" << price;
		}
	}
	else
		cout << "\nSorry, I am unable to open the file.\n";
	inFile.close();
	cout << "\n\nFLIGHT PRICE GRAPH MATRIX\n";
	matrix->printGraph();
	cout << endl;
	return matrix;
}

/*
	Title: printStringArray
	Purpose:  this function will print the array of strings with a space
		between each string
*/
void printStringArray(string* arr, int size)
{
	for(int x=0; x<size; x++)
	{
		cout << arr[x] << " ";
	}
}


// Function to generate lexicographic permutations of the given array
void lexicographic(string *arr, int size, Tour *tourOptions, GraphMatrix *matrix, int left, int right, int& index) 
{
    // When the left index is equal to the right index (termination condition for recursion)
    if (left == right) 
	{
        // Save the generated permutation with its cost
        saveTour(tourOptions, arr, size, matrix, index);
        index++; 
    } 
	else 
	{
        // Generate all possible permutations by swapping elements
        for (int i = left; i <= right; i++) 
		{
            // Swap elements to create different permutations
            swap(arr[left], arr[i]);
            // Recursively call lexicographic to generate permutations 
            lexicographic(arr, size, tourOptions, matrix, left + 1, right, index);
            // Swap elements back to original positions to continue generating permutations
            swap(arr[left], arr[i]);
        }
    }
}

// Function to save the tour with its total cost
void saveTour(Tour *tourOptions, string *arr, int size, GraphMatrix *matrix, int index) 
{
    int totalCost = 0;
    // Append "US" to the start and end of the tour
    tourOptions[index].tour[0] = "US";
    for (int i = 0; i < size; i++) 
	{
        // Assign the countries of the current permutation to the Tour array
        tourOptions[index].tour[i + 1] = arr[i];
        tourOptions[index].tour[size + 1] = "US";
    }

    // Calculate the total cost for the tour by adding the cost of each element
    for (int i = 0; i <= size; i++) 
	{
        string country1 = tourOptions[index].tour[i];
        string country2 = tourOptions[index].tour[i + 1];
        // Obtain the cost of traveling between two countries and add it to the total cost
        totalCost += matrix->getWeight(searchCountryCode(country1), searchCountryCode(country2));
    }

    // Save the total cost to the Tour array for the specific permutation
    tourOptions[index].cost = totalCost;
}
