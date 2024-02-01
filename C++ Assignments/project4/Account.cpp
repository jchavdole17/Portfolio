// File Name: Account.cpp
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code implements the Account class. 
                        This is a base clase, so many virtual functions are
                        used.
*/

#include "Account.h"
#include <iostream>
using namespace std;

//***********************************************************
// Written By: Juan Chavarria
// deposit: increases the balance and deposit statistics
// d: float value that indicates deposit amount
// 
// returns: void
//***********************************************************
void Account::deposit(float d)
{
    balance += d;
    dTotal += d;
    deposits += 1;
}


//***********************************************************
// Written By: Juan Chavarria
// withdraw: decreases the balance and increases withdrawal statistics
// w: negative float value that indicates withdrawal amount
// 
// returns: void
//***********************************************************
void Account::withdraw(float w)
{
    balance += w;
    wTotal += abs(w);
    withdrawals += 1;
}


//***********************************************************
// Written By: Juan Chavarria
// calcInt: calculates monthly interest based on current balance.
//          Adds interest to the balance.
// 
// returns: void
//***********************************************************
void Account::calcInt()
{
    float monRate, monIn;

    if (balance > 0) // allow interest only on positive balance accounts
    {
        monRate = rate/12;
        monIn = balance * monRate;
        iTotal += monIn;
        balance += monIn;
    }
}


//***********************************************************
// Written By: Juan Chavarria
// monthlyProc: add charges to the account, calculate the interest
//              and reset count variables to 0 to restart month count
// 
// returns: void
//***********************************************************
void Account::monthlyProc()
{
    balance -= charges; 
    chTotal += charges;
    Account::calcInt();
    withdrawals = 0;
    deposits = 0;
    charges = 0;
}