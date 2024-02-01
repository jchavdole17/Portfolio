// File Name: Checking.h
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code declares the class structure
                        of the Checking class.
*/

#ifndef CHECKING_H
#define CHECKING_H
#include "Account.h"
#include <iostream>

class Checking : public Account
{
    public:
        Checking(float b, float r) : Account(b, r)
            {}
        void withdraw(float);
        void monthlyProc();
};

#endif