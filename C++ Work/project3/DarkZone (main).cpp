// File Name: DarkZone.cpp
//
// Authors: Juan Chavarria
// Date: 11/10/2023
// Assignment Number 3
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This program reads in a text file with a capsule
                        capacity, and a group name and size, and uses it to
                        write to a text file that groups the groups into 
                        capsules based on input order and returns the 
                        utilization rate.
*/


#include <fstream>
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Stack.h"
#include "Node.h"
using namespace std;

// Function Prototypes
void writeOutput(Stack&, int, int);
void endStats(float, float);

// Global Variables
ifstream INFILE; // Input file
ofstream OUTFILE; // Resulting output file
int CAP_SIZE; // Capsule capacity

//***********************************************************
// Written By: Juan Chavarria
// main: has logic that empties queue and checks stack order
//
// returns: void/nothing 
//***********************************************************
int main()
{
    Queue que;
    Stack st;
    Node temp;
    int grSize, totPpl = 0, capNum = 0; 
    int currCapCount = 0;
    string name;

    // Store capsule size
    INFILE.open("DarkZone.txt");
    INFILE >> CAP_SIZE;

    // Store everything in a queue
    while (INFILE >> name >> grSize)
    {
        totPpl += grSize;
        que.enqueue(name, grSize);
    }
    INFILE.close();
   

    OUTFILE.open("Result.txt");
    while (que.peek() != nullptr)
    {
        temp = *que.peek(); // copy node values

        // Break code if a group has a size larger than the capacity
        if (temp.size > CAP_SIZE)
        {
            cout << "Group size is larger than the maximum capsule capacity.";
            cout << endl;
            break;
        }

        // check if the current capsule will surpass limit with new group size
        if ((currCapCount + temp.size) <= CAP_SIZE)
        {
        
            st.push(temp.name, temp.size);
            que.dequeue();
            currCapCount += temp.size;
        }

        // Write current full capsule to output file
        else
        {
            capNum += 1;
            writeOutput(st, currCapCount, capNum);
            currCapCount = 0;
            
        }

        // Release last values in stack if queue is about to finish
        if (temp.next == nullptr && st.length() > 0)
        {
            capNum += 1;
            writeOutput(st, currCapCount, capNum);
        }
    }

    endStats(totPpl, capNum);
    return 0;
}


//***********************************************************
// Written By: Juan Chavarria
// writeOutput: writes the total number of people, the group and their size,
//              and the capsule number to the output text file.
//
// &s: stack object reference that holds the group info for current capsule
// capCount: int that has the total number of people that fit in this capsule
// capNum: the capsule number that's being written to (starts at 1)
// returns: void/nothing (changes are seen on the output text file)
//***********************************************************
void writeOutput(Stack& s, int capCount, int capNum)
{
    Node* curr = nullptr;
    int len = s.length();

    OUTFILE << "Capsule #" << capNum << endl;
    for (int i = 0; i < len; i++)
    {
        curr = s.peek();
        OUTFILE << curr->name << " " << curr->size << endl;
        s.pop();
    }

    OUTFILE << "Total Guests: " << capCount << endl;
    OUTFILE << "Remaining capacity: " << (CAP_SIZE-capCount) << endl << endl;
}


//***********************************************************
// Written By: Juan Chavarria
// endStats: writes stats (total number of guests, capsules, and utitilzation)
//           to output text file
//
// totalPpl: int that represents the total number of people of all groups
// totalCap: int that has the total number of capsules used to seat all groups
// returns: void/nothing (changes are seen on the output text file)
//***********************************************************
void endStats(float totalPpl, float totalCap)
{
    float percentUtil = (totalPpl/(totalCap*CAP_SIZE))*100;

    OUTFILE << "Overall Number of guests: " << totalPpl << endl;
    OUTFILE << "Overall number of capsules: " << totalCap << endl;
    OUTFILE << "Capsule capacity: " << CAP_SIZE << endl;
    OUTFILE << "Percentage Utilization: " << totalPpl << "/(" << totalCap;
    OUTFILE << "*" << CAP_SIZE << ") = " << setprecision(1) << fixed;
    OUTFILE << percentUtil << "%" << endl;
    
    OUTFILE.close();
}