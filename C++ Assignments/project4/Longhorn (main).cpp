// File Name: Longhorn.cpp
//
// Authors: Juan Chavarria
// Date: 12/01/2023
// Assignment Number 5
// CS 105C Fall 2023
// Instructor: Dr. Palacios
/* Program Description: This code focuses on simulating a program that takes 
                        care of user bank transactions. This code implements
                        3 classes: an regular account, a savings account, and
                        a checking account. The savings and checking accounts
                        implement their differences in their own classes, and
                        call a base method from the regular account class. The
                        program here reads a text file with two different 
                        account information and transaction info, and returns
                        the end of month statistics for each account in a text
                        file.
*/

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Account.h"
#include "Checking.h"
#include "Savings.h"
using namespace std;

// Function Prototypes
Account* createAcc(float&, string&);
void displayTran(Account*, float&, string&);
void monthStats(Account*, float&);

// Constants
ifstream INFILE;
ofstream OUTFILE;

//***********************************************************
// Written By: Juan Chavarria
// main: processes the 2 accounts from the transactions.txt file
//       and writes to the output file.
//
// returns: 0 for successful run
//***********************************************************
int main()
{
    float tran, begBal;
    string accType;
    Account* acc;
    Account* acc2;

    INFILE.open("transactions.txt");
    OUTFILE.open("results.txt");
    OUTFILE << setprecision(2) << fixed;

    // Process first account
    acc = createAcc(begBal, accType);
    while (INFILE >> tran) // Read transaction values
        displayTran(acc, tran, accType); // Process transaction
    monthStats(acc, begBal);
   
    INFILE.clear();
    OUTFILE << endl;

    // Process second account
    acc2 = createAcc(begBal, accType);
     while (INFILE >> tran)
        displayTran(acc2, tran, accType);
    monthStats(acc2, begBal);

    // Delete dynamically allocated memory
    INFILE.close();
    OUTFILE.close();
    delete acc;
    acc = nullptr;
    delete acc2;
    acc2 = nullptr;

    return 0;
}

//***********************************************************
// Written By: Juan Chavarria
// createAcc: reads input text file, creates account class, and stores account
//            stats to reference input parameters. 
// &bBal: float reference that represents the beginning balance of an account
// &accType: string reference that stores the account type
// 
// returns: account class pointer holding a savings or checking object
//***********************************************************
Account* createAcc(float& bBal, string& accType)
{
    float annRate, transaction;
    Account* acc = nullptr;

    INFILE >> accType >> bBal >> annRate;

    // Write to output file
    OUTFILE << "Account Type: " << accType << endl;
    OUTFILE << "TRANSACTIONS: " << endl;

    // Check what type of account to create
    if (accType == "checking")
        acc = new Checking(bBal, annRate);

    else if (accType == "savings")
        acc = new Savings(bBal, annRate);
       
    return acc;
}

//***********************************************************
// Written By: Juan Chavarria
// displayTran: processes withdrawals and deposits, and writes transaction 
//              to output file 
// Account*: Account object pointer used to process transactions
// &tran: float reference to transaction amount value read in main
// &accType: string reference that stores the account type 
// 
// returns: void. Writes to results.txt.
//***********************************************************
void displayTran(Account* accVar, float& tran, string& accType)
{
    
    if (tran < 0) // withdrawals
    {
        if ((accType == "savings") and (accVar->balance < 25))
            OUTFILE << "Withdrawal (Invalid): $" << abs(tran) << endl; 
        else if ((accType == "savings") and (accVar->balance + tran < 0))
            OUTFILE << "Withdrawal (Invalid): $" << abs(tran) << endl; 
        else if ((accType == "checking") and (accVar->balance + tran < 0))
            OUTFILE << "Withdrawal (Invalid): $" << abs(tran) << endl; 
        else
            OUTFILE << "Withdrawal (Success): $" << abs(tran) << endl; 

        accVar->withdraw(tran);
    }

    else if (tran > 0) // deposits
    {
        accVar->deposit(tran);
        OUTFILE << "Deposit: $" << tran << endl; 
    }
}


//***********************************************************
// Written By: Juan Chavarria
// monthStats: writes to results.txt the end of month stats of the account
// Account*: Account object pointer used to retrieve stats
// &bBal: float reference that represents the beginning balance of an account
// 
// returns: void. Writes to results.txt.
//***********************************************************
void monthStats(Account* acc, float& bBal)
{
    acc->monthlyProc();
    OUTFILE << "SUMMARY" << endl;
    OUTFILE << "Beginning Balance: $" << bBal << endl;
    OUTFILE << "Deposits Total: $" << acc->dTotal << endl;
    OUTFILE << "Withdrawals Total: $" << acc->wTotal << endl;
    OUTFILE << "Interest Accumulated: $" << acc->iTotal << endl;
    OUTFILE << "Service Charge Fees: $" << acc->chTotal << endl;
    OUTFILE << "Final Balance: $" << acc->balance << endl;
}