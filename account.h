#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <cstdlib> //rand()

class Account {
    private:
        std::string name_;
        int balance_;
        int accountNumber_;
        int routingNumber_;
    public:
        Account();
        Account(const std::string& name);
        Account(const std::string& name, const int& balance);
        Account(const std::string& name, const int& balance, const int& accountNumber, const int& routingNumber);
        Account(const Account& other);
        ~Account();
        Account& operator=(const Account& other);
        std::string getName() const;
        bool zeroBalance() const;
        int getBalance() const;
        int getAccountNumber() const;
        int getRoutingNumber() const;
        void setName(const std::string& name);
        void setBalance(const int& balance);
        void setAccountNumber(const int& accountNumber);
        void setRoutingNumber(const int& routingNumber);
};

#endif
