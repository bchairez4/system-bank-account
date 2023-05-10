#ifndef CLIENT_H
#define CLIENT_H

#include "user.cpp"
#include "account.cpp"
#include <vector>

class Client {
    private:
        User user_;
        std::vector<Account> accounts_;
    public:
        Client();
        Client(const User& user, const std::vector<Account>& accounts);
        Client(const Client& other);
        ~Client();
        Client& operator=(const Client& other);
        User getUser() const;
        std::vector<Account> getAccounts() const;
        void updateUserName(const std::string& fName, const std::string& lName);
        void updateUserEmail(const std::string& email);
        void updateUserPassword(const std::string& password);
        void updateAccountName(const std::string& accountName, const std::string& updatedName);
        void addAccount(const Account& account);
        void removeAccount(const std::string& accountName);
        bool contains(const std::string& accountName) const;
};

#endif
