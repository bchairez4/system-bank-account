#ifndef CLIENT_H
#define CLIENT_H

#include "user.cpp"
#include "account.cpp"
#include <vector>

// Derived Class
// A Client is a User and has a pin number and list containing their account(s)
class Client : public User {
    private:
        int pin_;
        std::vector<Account> accounts_;
    public:
        Client();
        Client(const std::string& fName, const std::string& lName, const std::string& email, const std::string& password, const int& pin);
        Client(const std::string& fName, const std::string& lName, const std::string& email, const std::string& password, const int& pin, const std::vector<Account>& accounts);
        Client(const Client& other);
        ~Client();
        Client& operator=(const Client& other);
        int getPin() const;
        std::vector<Account> getAccounts() const;
        void updateUserName(const std::string& fName, const std::string& lName);
        void updateUserEmail(const std::string& email);
        void updateUserPassword(const std::string& password);
        void updatePin(const int& pin);
        void updateAccountName(const std::string& accountName, const std::string& updatedName);
        void addAccount(const Account& account);
        void removeAccount(const std::string& accountName);
        bool contains(const std::string& accountName) const;
};

#endif
