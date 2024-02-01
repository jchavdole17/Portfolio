// File Name: Savings.cpp
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code implements the Savings class. 
                        This is a class overrides many functions from 
                        the Account class.
*/

#include "Savings.h"
#include "Account.h"
#include <iostream>
using namespace std;


//***********************************************************
// Written By: Juan Chavarria
// withdraw: Overrides base class method. Checks account status 
//           before and after calling the base withdrawal function.
// w: negative float value that indicates withdrawal amount
// 
// returns: void
//***********************************************************
void Savings::withdraw(float w)
{
    if (status == true)
        if (balance + w >= 0) // prevent withdrawal greater than balance
            Account::withdraw(w);
            if (balance < 25) // check account status after withdrawal
                status = false;
}


//***********************************************************
// Written By: Juan Chavarria
// deposit: Overrides base class method. Deposits desired amount,
//          and evaluates account status after the deposit
// d: float value that indicates deposit amount
// 
// returns: void
//***********************************************************
void Savings::deposit(float d)
{
    if (status == false)
    {
        if ((balance + d) >= 25)
        {
            status = true;
            Account::deposit(d);
        }

        else
            Account::deposit(d);
    }

    else
        Account::deposit(d);
}


//***********************************************************
// Written By: Juan Chavarria
// monthlyProc: Override of base class function. Service fees added
//              to charges, and then the base function is called. The
//              account status is recalculated after that.
// 
// returns: void
//***********************************************************
void Savings::monthlyProc()
{
    if (withdrawals > 4)
    {
        charges += (withdrawals - 4);
        Account::monthlyProc(); 

        if (balance < 25)
            status = false;
    }

    else
        Account::monthlyProc();
}