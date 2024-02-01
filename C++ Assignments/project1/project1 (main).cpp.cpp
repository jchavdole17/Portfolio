// File Name: Project1_jac23763_taa2425.cpp
//
// Authors: Juan Chavarria, Talal Al-Otaibi
// Date: 9/29/2023
// Assignment Number 1
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This program takes an input file that states the number
                        of articles present and lists their titles, popularity,
                        and web page links. The program stores this in an array 
                        of structs, and returns the mode of the popularity 
                        scores of all the articles as well as the articles that
                        have a score equal to the mode.
*/

#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Global Constants
ifstream infile; // Used in functions so declared in full scope of code

// Struct to store story information
struct story
{
    string headline;
    string URL;
    int score;
};

// Function prototypes
void read_stories(story *ptr, int);
void display_stories(story *ptr,int, int);
int findMode(story *ptr, int);

int main()
{
    // Define variables
    string fileName, n;
    int numStories = 0;
    int mode;

    // Request file
    cout << "Type the file you want to read (press Enter when you're done): " ;
    getline(cin, fileName);
    infile.open(fileName);
    
    // Dynamically allocate memory
    getline(infile, n); // Check how many stories there are
    numStories = stoi(n); // convert string input to integer
    story *arrPtr = nullptr;
    arrPtr = new story[numStories];
    

    // Read file, find mode, and display results
    read_stories(arrPtr, numStories);
    mode = findMode(arrPtr, numStories);
    display_stories(arrPtr, mode, numStories);
}



void display_stories(story *stories, int mode, int size)
{
    if (mode != -1)
    {
        cout << endl << "Mode: " << mode << endl << endl;
        for (int i = 0; i < size; i++)
        {
            if ((*(stories+i)).score == mode)
                cout << (*(stories + i)).headline << endl << (*(stories+i)).URL << endl << endl;
        }
    }

    else
    {
        cout << endl << "Mode: No mode was found." << endl << endl;

        if (size >= 5)
        {
            for (int i = 0; i < 5; i++)
                cout << (*(stories + i)).headline <<  endl << (*(stories+i)).URL <<  endl << endl;
        }

        else
        {
            for (int i = 0; i < size; i++)
                cout << (*(stories + i)).headline <<  endl << (*(stories+i)).URL <<  endl << endl;
        }
    }
}

//***********************************************************
// Written By: Juan Chavarria
// findMode: Searches array of story structs to find the popularity score mode
//
// *stories: pointer to an array of structs that holds info of each story 
// size: integer variable denoting the number of stories in stories array
// returns: integer value of the popularity score mode             
//***********************************************************
int findMode(story *stories, int size)
{
    /* Set variables to store results throughout the function since we
       will use parallel arrays to find the mode.
    */
    int scoreArr[size], countArr[size];
    int mode = -1000, frequency = 0;
    
    // Store each story's popularity score in score_arr
    for (int i = 0; i < size; i++)
    {
        *(scoreArr + i) = (*(stories+i)).score;
    }
    
    // Count how many times a story's score appears in the whole file 
    for (int i = 0; i < size; i++)
    {
        *(countArr+i) = count(scoreArr, scoreArr+size,*(scoreArr+i));
    }

    // Traverse count_arr to find the max frequency, which is the mode 
    for (int i = 0; i < size; i++)
    {
        // Update the frequency and mode value as array traversal continues
        if (*(countArr+i) > frequency)
        {
            frequency = *(countArr+i);
            mode = (*(stories+i)).score;
        }
    }

    /* If the resulting frequency was 1, then all scores appeared once
       in the file. Thus, there was no mode found. Else, you want to 
       return the most value of the most frequent appearing score.
    */
    if (frequency == 1)
        return -1;
    else
        return mode;
}


//***********************************************************
// Written By: Juan Chavarria
// read_stories: Populates the array of story structs with info from each story
//
// *arr: pointer to array of structs created in main to store story info
// num_stories: integer that says how many stories we have to extract info from
// returns: void function | populates array from input pointer              
//***********************************************************
void read_stories(story *arr, int num_stories)
{
    string scoreHolder; // Stores getline() result since it returns a string

    // Iterate through all stories in input file to store in struct array
    for (int i = 0; i < num_stories; i++)
    { 
        // Extract each story's 3 attributes (headline, URL, score)
        getline(infile, (*(arr + i)).headline);
        getline(infile, (*(arr + i)).URL);
        getline(infile, scoreHolder);
        (*(arr + i)).score = stoi(scoreHolder); // convert getline result
    }
}
