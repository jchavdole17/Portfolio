// File Name: Checking.cpp
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code implements the Checking class. 
                        This is a class overrides many functions from 
                        the Account class.
*/

#include "Checking.h"
#include "Account.h"
#include <iostream>
using namespace std;

//***********************************************************
// Written By: Juan Chavarria
// withdraw: Overrides base class method. Prevents withdrawals greater
//           than the account balance, and adds fees if attempted.
// w: negative float value that indicates withdrawal amount
// 
// returns: void
//***********************************************************
void Checking::withdraw(float w)
{
    if ((balance + w) < 0)
        charges += 15;

    else
        Account::withdraw(w);
}

//***********************************************************
// Written By: Juan Chavarria
// monthlyProc: Override of base class function. Service fees added
//              to charges, and then the base function is called.
// 
// returns: void
//***********************************************************
void Checking::monthlyProc()
{
    charges += 5 + (withdrawals * 0.10);
    Account::monthlyProc();
}