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
        void displayUserInfo() const;
        void displayDatabase() const;
        bool authorize(const int& pin) const;
        void signIn(const std::string& email, const std::string& password);
        void signOut();
        void addCustomer(const Client& client);
        void removeCustomer(const Client& client);
        void addAccount(const Client& client, const Account& account);
        void closeAccount(const Client& client, const std::string& accountName);
        void deposit(const int& pin, const std::string& accountName, const int& amount);
        void withdrawl(const int& pin, const std::string& accountName, const int& amount);
};

#endif
