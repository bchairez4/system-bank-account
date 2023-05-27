#ifndef CLIENT_H
#define CLIENT_H

#include "user.cpp"
#include "account.cpp"
#include <iostream>
#include <vector>

// Derived Class
// A Client is a User and has a pin number and a vector of their account(s)
class Client : public User {
    private:
        int pin_;
        std::vector<Account> accounts_;
    public:
        Client();
        Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin);
        Client(const std::string& firstName, const std::string& lastName, const std::string& emial, const std::string& password, const int& pin, const std::string& accountName);
        Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin, const std::vector<Account>& accounts);
        Client(const Client& other);
        ~Client();
        Client& operator=(const Client& other);
        int getPin() const;
        Account getAccount(const std::string& accountName) const;
        std::vector<Account> getAccounts() const;
        int getAccountBalance(const std::string& accountName) const;
        bool contains(const std::string& accountName) const;
        void displayUser() const;
        void displayAccounts() const;
        void updateUser(const Client& client);
        void updatePin(const int& pin);
        void updateAccount(const Account& oldAccount, const Account& newAccount);
        void updateAccounts(const std::vector<Account>& accounts);
        void updateAccountName(const std::string& accountName, const std::string& updatedName);
        void updateAccountBalance(const std::string& accountName, const int& balance);
        void addAccount(const Account& account);
        void removeAccount(const std::string& accountName);
};

#endif
