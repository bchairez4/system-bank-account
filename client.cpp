#include "client.h"

#define ONE 1

Client::Client() : pin_(-ONE), accounts_(ONE, Account()) {}

Client::Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin)
: User(firstName, lastName, email, password), pin_(pin), accounts_(ONE, Account()) {}

Client::Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin, const std::vector<Account>& accounts)
: User(firstName, lastName, email, password), pin_(pin), accounts_(accounts) {}

Client::Client(const Client& other) 
: User(other.getFirstName(), other.getLastName(), other.getEmail(), other.getPassword()), pin_(other.pin_), accounts_(other.accounts_) {}

Client::~Client() {}

Client& Client::operator=(const Client& other) {
    User(other.getFirstName(), other.getLastName(), other.getEmail(), other.getPassword());
    pin_ = other.pin_;
    accounts_ = other.accounts_;
    return *this;
}

int Client::getPin() const {
    return pin_;
}

std::vector<Account> Client::getAccounts() const {
    return accounts_;
}

int Client::getAccountBalance(const std::string& accountName) const {
    for (int i = 0; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == accountName) {
            return accounts_[i].getBalance();
        }
    }

    return -1;
}

bool Client::contains(const std::string& accountName) const {
    for (int i = 0; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == accountName) {
            return true;
        }
    }

    return false;
}

void Client::displayUser() const {
    std::cout << "Name: " << getFullName() << '\n'
              << "Email: " << getEmail() << '\n';
    std::cout << '\n';
}

void Client::displayAccounts() const {
    for (std::vector<Account>::const_iterator it = accounts_.cbegin(); it != accounts_.cend(); ++it) {
        std::cout << "\"" << it->getName() << "\"" << " Account:" << '\n'
              << "Balance: $" << it->getBalance() << '\n'
              << "Account Number: " << it->getAccountNumber() << '\n'
              << "Routing Number: " << it->getRoutingNumber() << '\n';
        
        std::cout << '\n';
    }
}

void Client::updateUserName(const std::string& firstName, const std::string& lastName) {
    if (firstName.empty() || lastName.empty()) {
        return;
    }

    setName(firstName, lastName);
}

void Client::updateUserEmail(const std::string& email) {
    if (email.empty()) {
        return;
    }

    setEmail(email);
}

void Client::updateUserPassword(const std::string& password) {
    if (password.empty()) {
        return;
    }

    setPassword(password);
}

void Client::updatePin(const int& pin) {
    if (pin < 0 || pin > 999999) {    //6-digit limit for pin number
        return;
    }

    pin_ = pin;
}

void Client::updateAccounts(const std::vector<Account>& accounts) {
    accounts_ = accounts;
}

void Client::updateAccountBalance(const std::string& accountName, const int& amount) {
    for (int i = 0; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == accountName) {
            accounts_[i].setBalance(amount);
        }
    }
}

void Client::updateAccountName(const std::string& accountName, const std::string& updatedName) {
    if (accountName.empty() || updatedName.empty()) {
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

bool Client::removeAccount(const std::string& accountName) {
    if (!contains(accountName)) {
        return false;
    }

    std::vector<Account>::iterator it = accounts_.begin();
    for (; it != accounts_.end(); ++it) {
        if (it->getName() == accountName) {
            break;
        }
    }

    if (!it->zeroBalance()) {   //can't close an account that still has money in it
        return false;
    }

    accounts_.erase(it);
    return true;
}
