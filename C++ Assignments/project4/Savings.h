// File Name: Savings.h
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code declares the class structure
                        of the Savings class.
*/

#ifndef SAVINGS_H
#define SAVINGS_H
#include "Account.h"
#include <iostream>

class Savings : public Account
{
    public:
        bool status;
    
        Savings(float b, float r) : Account(b, r)
            {
                if (b >= 25)
                    status = true;
                else
                    status = false;
            }
        void withdraw(float);
        void deposit(float);
        void monthlyProc();

};
#endif