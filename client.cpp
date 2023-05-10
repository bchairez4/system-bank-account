#include "client.h"

Client::Client() {}

Client::Client(const User& user, const int& pin, const std::vector<Account>& accounts)
: user_(user), pin_(pin), accounts_(accounts) {}

Client::Client(const Client& other) : user_(other.user_), pin_(other.pin_), accounts_(other.accounts_) {}

Client::~Client() {}

Client& Client::operator=(const Client& other) {
    user_ = other.user_;
    pin_ = other.pin_;
    accounts_ = other.accounts_;
    return *this;
}

User Client::getUser() const {
    return user_;
}

int Client::getPin() const {
    return pin_;
}

std::vector<Account> Client::getAccounts() const {
    return accounts_;
}

bool Client::contains(const std::string& accountName) const {
    for (int i = 0; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == accountName) {
            return true;
        }
    }

    return false;
}

void Client::updateUserName(const std::string& fName, const std::string& lName) {
    if (fName.empty() || lName.empty()) {
        return;
    }

    user_.setName(fName, lName);
}

void Client::updateUserEmail(const std::string& email) {
    if (email.empty()) {
        return;
    }

    user_.setEmail(email);
}

void Client::updateUserPassword(const std::string& password) {
    if (password.empty()) {
        return;
    }

    user_.setPassword(password);
}

void Client::updatePin(const int& pin) {
    pin_ = pin;
}

void Client::updateAccountName(const std::string& accountName, const std::string& updatedName) {
    if (updatedName.empty()) {
        return;
    }

    if (!contains(accountName)) {
        return;
    }

    for (int i = 0; i < accounts_.size(); ++ i) {
        if (accounts_[i].getName() == accountName) {
            accounts_[i].setName(updatedName);
        }
    }
    
}

void Client::addAccount(const Account& account) {
    if (contains(account.getName())) {
        return;
    }

    accounts_.push_back(account);
}

void Client::removeAccount(const std::string& accountName) {
    if (!contains(accountName)) {
        return;
    }

    std::vector<Account>::iterator it = accounts_.begin();
    for (; it != accounts_.end(); ++it) {
        if (it->getName() == accountName) {
            break;
        }
    }

    accounts_.erase(it);
}
