#ifndef SYSTEM_H
#define SYSTEM_H

#include "authentication.cpp"

class System {
    private:
        Authentication token_;
        Database database_;
    public:
        System();
        System(const System& other);
        ~System();
        System& operator=(const System& other);
        Authentication getToken() const;
        Client getClient(const std::string& email) const;
        Database getDatabase() const;
        void displayUserInfo() const;
        void displayDatabase() const;
        bool authorize(const int& pin) const;
        bool contains(const std::string& email) const;
        bool containsCustomerAccount(const Client& client, const std::string& accountName) const;
        bool isSignedInCustomer() const;
        bool isSignedInAdmin() const;
        void signIn(const std::string& email, const std::string& password);
        void signOut();
        void addCustomer(const Client& client);
        void removeCustomer(const Client& client);
        void updateCustomer(const Client& oldClient, const Client& newClient);
        Account getCustomerAccount(const Client& client, const std::string& accountName) const;
        int getCustomerAccountBalance(const Client& client, const std::string& accountName) const;
        void addAccount(const Client& client, const Account& account);
        void closeAccount(const Client& client, const std::string& accountName);
        void updateCustomerAccount(const Client& client, const Account& oldAccount, const Account& newAccount);
        void deposit(const int& pin, const std::string& accountName, const int& amount);
        void withdrawl(const int& pin, const std::string& accountName, const int& amount);
};

#endif
