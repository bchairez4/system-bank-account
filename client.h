#ifndef CLIENT_H
#define CLIENT_H

#include "user.cpp"
#include "account.cpp"
#include <iostream>
#include <vector>

// Derived Class
// A Client is a User and has a pin number and list containing their account(s)
class Client : public User {
    private:
        int pin_;
        std::vector<Account> accounts_;
    public:
        Client();
        Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin);
        Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin, const std::vector<Account>& accounts);
        Client(const Client& other);
        ~Client();
        Client& operator=(const Client& other);
        int getPin() const;
        std::vector<Account> getAccounts() const;
        bool contains(const std::string& accountName) const;
        void displayUser() const;
        void displayAccounts() const;
        void updateUserName(const std::string& firstName, const std::string& lastName);
        void updateUserEmail(const std::string& email);
        void updateUserPassword(const std::string& password);
        void updatePin(const int& pin);
        void updateAccounts(const std::vector<Account>& accounts);
        void updateAccountName(const std::string& accountName, const std::string& updatedName);
        void addAccount(const Account& account);
        bool removeAccount(const std::string& accountName);
};

#endif
