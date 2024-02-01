#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include <string>
using namespace std;


class PasswordManager
{
    private:
        string username;
        string password; //has to be encrypted
        string encrypt(string);
        bool meetsCriteria(string);
    public: 
        PasswordManager();
        ~PasswordManager();
        void setUsername(string);
        void setEncryptedPassword(string);
        string getUsername() const;
        string getEncryptedPassword() const;
        bool setNewPassword(string);
        bool authenticate(string);
};

#endif