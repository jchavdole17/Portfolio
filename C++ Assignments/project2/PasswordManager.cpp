#include <string>
#include "PasswordManager.h"
using namespace std;

//***********************************************************
// Written By: Juan Chavarria
// PasswordManager: class constructor
// 
// returns: PasswordManager object initialized to empty strings
//***********************************************************
PasswordManager::PasswordManager()
{
    username = "";
    password = "";
}

//***********************************************************
// Written By: Juan Chavarria
// ~PasswordManager: class destructor
// 
// returns: PasswordManager object destroyed
//***********************************************************
PasswordManager::~PasswordManager()
{}

//***********************************************************
// Written By: Juan Chavarria
// encrypt: encrypt a string using Caesar's cipher
// pword: input string that needs to be encrypted
// returns: string that's an encrypted form password
//***********************************************************
string PasswordManager::encrypt(string pword)
{
    string epass = pword;
    char *eptr = nullptr;
    int asciiVal;
    int pwordLen = pword.length();

    for (int i = 0; i < pwordLen; i++)
    {
        // Caesar's Cipher for every character
        eptr = &epass[i];
        asciiVal = (int) *eptr;
        *eptr = char (((asciiVal - 33) + 25) % 94 + 33);
    }
    return epass;
}

//***********************************************************
// Written By: Juan Chavarria
// meetsCriteria: checks if password has 8 characters, 1 upper & lowercase
//                character, and 1 digit.
// pword: input string that needs to be checked for criteria
// returns: bool confirming if criteria was met
//***********************************************************
bool PasswordManager::meetsCriteria(string pword)
{
    // Check for string length
    if (pword.length() < 8)
        return false;

    bool checks[3] = {false, false, false};
    int sum = 0, pwordLen = pword.length();
    char val;

    // check criteria for every character
    for (int i = 0; i < pwordLen; i++)
    {
        val = pword[i];
        if (isupper(val))
            {*(checks+0) = true;}
        else if (islower(val))
            {*(checks+1) = true;}
        else if (isdigit(val))
            {*(checks+2) = true;}
    }

    // Check if all boolean array values are True
    for (int i = 0; i < 3; i++)
        sum += *(checks+i);

    if (sum == 3)
        return true;
    else 
        return false;
}

//***********************************************************
// Written By: Juan Chavarria
// setUsername: mutator for username
// uName: string with new username input
// returns: void
//***********************************************************
void PasswordManager::setUsername(string uName)
{username = uName;}

//***********************************************************
// Written By: Juan Chavarria
// setEncryptedPassword: mutator for password
// ePword: string of new encrypted password
// returns: void
//***********************************************************
void PasswordManager::setEncryptedPassword(string ePword)
{password = ePword;}

//***********************************************************
// Written By: Juan Chavarria
// getUsername: accessor for username
// returns: string with private data (username)
//***********************************************************
string PasswordManager::getUsername() const
{return username;}

//***********************************************************
// Written By: Juan Chavarria
// getEncryptedPassword: accessor for password
// returns: string with private data (encrypted password)
//***********************************************************
string PasswordManager::getEncryptedPassword() const
{return password;}

//***********************************************************
// Written By: Juan Chavarria
// setNewPassword: takes a string and attempts setting it as object password
// nPword: input string that will be set as new password
// returns: bool confirming if password was set
//***********************************************************
bool PasswordManager::setNewPassword(string nPword)
{
    if (meetsCriteria(nPword))
    {
        setEncryptedPassword(encrypt(nPword));
        return true;
    }
    else
        return false;
}

//***********************************************************
// Written By: Juan Chavarria
// authenticate: checks if input string matches encrypted password on file
// pword: input password to be checked
// returns: bool that confirms if the password matched the one in the object
//***********************************************************
bool PasswordManager::authenticate(string pword)
{
    string ePword = encrypt(pword);

    // Check if the stored encrypted password matches
    if (getEncryptedPassword() == ePword)
        return true;
    else
        return false;
}