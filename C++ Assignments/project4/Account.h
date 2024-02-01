// File Name: Account.h
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code declares the class structure
                        of the Account class.
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>
using namespace std;

class Account
{
    public:
        float balance;
        float deposits;
        float dTotal = 0, wTotal = 0, iTotal = 0, chTotal = 0;
        float withdrawals;
        float rate;
        float charges;

        Account(float b, float r) // Constructor
            {
                balance = b; rate = r/100; charges = 0;
                deposits = 0; withdrawals = 0;
            }
        
        virtual void deposit(float);
        virtual void withdraw(float);
        virtual void monthlyProc();

    protected:
        virtual void calcInt();
};

#endif