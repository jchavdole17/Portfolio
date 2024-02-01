// File Name: PasswordDriver.cpp
//
// Authors: Juan Chavarria, Talal Al-Otaibi
// Date: 10/20/2023
// Assignment Number 2
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This file stores 3 user credential given through a
                        a text file called "passwords.txt", and then prompts
                        the user to enter their credentials. If a username
                        match is found and the current password input is
                        correct, the password will be changed to the new 
                        one submitted by the user if it meets the criteria.
                        Finally, the changes are overwritten in the text file.
*/

#include <string>
#include <iostream>
#include <fstream>
#include "PasswordManager.h"
using namespace std;

// Function prototypes
bool readTextfile(PasswordManager*);
void displayCriteria(string*, string*, string*);
int matchUser(PasswordManager*, string*);
void passwordChange(PasswordManager*, int, string*, string*);
void writeOutput(PasswordManager*);

// Global Constants
ifstream INFILE;
ofstream OUTFILE;

//***********************************************************
// Written By: Talal Al-Otaibi
// main: stores 3 user credentials, requests user's credentials, verifies input
//       and updates the info, and lastly writes it to the text file
// 
// returns: 0 if successful, 1 if error or early break occured
//***********************************************************
int main()
{
    // Define Class, and user credentials
    PasswordManager user[3];
    string uname, oldPword, newPword;
    string *unamePtr = &uname, *oldPwordPtr = &oldPword, *newPwordPtr = &newPword;
    int user_match = -1; // represents if username match was found
    bool readfile = false; // represents successful file read
    
    // Save text file information
    readfile = readTextfile(user);
    if (readfile == false) // break if file didn't exist
        {return 1;}
    
    // Request information
    displayCriteria(unamePtr, oldPwordPtr, newPwordPtr);

    // Check if there was a username match 
    user_match = matchUser(user, unamePtr); // Find index of matching username
    if (user_match != -1)
       {passwordChange(user, user_match, oldPwordPtr, newPwordPtr);}
    else // no username match
        {cout << "Username is invalid, password not changed.";}

    writeOutput(user); // update text file
    return 0;
}

//***********************************************************
// Written By: Juan Chavarria
// readTextfile: opens txt file with username/password pairs and stores them
//               them in an array
// *user: array that holds 3 PasswordManager class objects
// returns: bool that confirms if file was written or not
//***********************************************************
bool readTextfile(PasswordManager* user)
{
    string uname, pword; 

    INFILE.open("passwords.txt");
    if (!INFILE) // Check if file exists
    {
        cout << "Input file does not exist" << endl;
        INFILE.close();
        return false;
    }

    // Save text file information
    for (int i = 0; i < 3; i++)
    {
        INFILE >> uname >> pword; // store credential pairs
        (user + i)->setUsername(uname);
        (user + i)->setEncryptedPassword(pword);
    }
    INFILE.close();
    return true;
}

//***********************************************************
// Written By: Juan Chavarria
// displayCriteria: requests input for username, current password, new password
//                  , and  new password 
// *uname: array that holds 3 PasswordManager class objects
// *oldPword: pointer to current password input attempt from user
// *newPword: pointer to new password input attempt from user
// returns: void | all changes are done through pointers
//***********************************************************
void displayCriteria(string* uname, string* oldPword, string* newPword)
{
    cout << "Passwords must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, and one digit to be valid.";
    cout << endl << "Please enter your username: ";
    getline(cin, *uname);
    cout << endl << "Please enter your old password: ";
    getline(cin, *oldPword);
    cout << endl << "Please enter your new password: ";
    getline(cin, *newPword);
    cout << endl;
}

//***********************************************************
// Written By: Talal Al-Otaibi
// matchUser: searches user array to find username match from user input
// *user: PasswordManager object array 
// *uname2: username input from user
// returns: integer that returns array index with matching username
//***********************************************************
int matchUser(PasswordManager* user, string* uname2)
{
    for (int i = 0; i < 3; i++)
    {
        // check for matching username
        if ((*uname2) == ((user+i)->getUsername()))
            {return i;}
    }
    return -1;
}

//***********************************************************
// Written By: Talal Al-Otaibi
// passwordChange: changes password in object array if authentication works
//                 and if the new password meets password criteria
// *user: array that holds 3 PasswordManager class objects
// user_match: array index of account that matched username input
// *oldPwordPtr: pointer to the old password used for authentication
// *newPwordPtr: pointer to new password needed to be stored in class
// returns: void | only prints if password passed
//***********************************************************
void passwordChange(PasswordManager* user, int user_match, string* oldPwordPtr, string* newPwordPtr)
{
    bool oldPwordMatch = false;
    bool pwordChange = false;

    // check authentication
    oldPwordMatch = (user+user_match)->authenticate(*oldPwordPtr);
        if (oldPwordMatch)
        {
            // check criteria of new password
            pwordChange = (user+user_match)->setNewPassword(*newPwordPtr);
            if (pwordChange)
            {
                cout << "Password has been changed for username: ";
                cout << (user+user_match)->getUsername() << endl;
                return;
            }
            else
            {
                cout << "New password does not meet criteria." << endl;
                return;
            }
        }
        else
        {
            cout << "Old password is incorrect." << endl;
            return;
        }
}

//***********************************************************
// Written By: Juan Chavarria
// writeOutput: rewrites text file with updated object
// *user: array of PasswordManager class objects
// returns: void | new text file
//***********************************************************
void writeOutput(PasswordManager* user)
{
    OUTFILE.open("passwords.txt");

    // Rewrite all data
    for (int i = 0; i < 3; i ++)
    {
        OUTFILE << (user+i)->getUsername() << " " << (user+i)->getEncryptedPassword() << endl; 
    }
    OUTFILE.close();
}