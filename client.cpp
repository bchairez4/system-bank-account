#include "client.h"

#define ONE 1
#define PIN_LIMIT 999999

Client::Client() : pin_(-ONE) {}

Client::Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin)
: User(firstName, lastName, email, password), pin_(pin), accounts_(ONE, Account()) {}

Client::Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin, const std::string& accountName) 
: User(firstName, lastName, email, password), pin_(pin), accounts_(ONE, Account(accountName)) {}

Client::Client(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password, const int& pin, const std::vector<Account>& accounts)
: User(firstName, lastName, email, password), pin_(pin) {
    for (int i = 0; i < accounts.size(); ++i) {
        accounts_.push_back(accounts[i]);
    }
}

Client::Client(const Client& other) 
: User(other.getFirstName(), other.getLastName(), other.getEmail(), other.getPassword()), pin_(other.pin_) {
    for (int i = 0; i < other.accounts_.size(); ++i) {
        accounts_.push_back(other.accounts_[i]);
    }
}

Client::~Client() {}

Client& Client::operator=(const Client& other) {
    setFirstName(other.getFirstName());
    setLastName(other.getLastName());
    setEmail(other.getEmail());
    setPassword(other.getPassword());
    pin_ = other.pin_;
    for (int i = 0; i < other.accounts_.size(); ++i) {
        accounts_.push_back(other.accounts_[i]);
    }
    return *this;
}

int Client::getPin() const {
    return pin_;
}

Account Client::getAccount(const std::string& accountName) const {
    for (int i = 0; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == accountName) {
            return accounts_[i];
        }
    }

    return Account();
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
    for (int i = 0; i < accounts_.size(); ++i) {
        std::cout << "\"" << accounts_[i].getName() << "\"" << " Account:" << '\n'
              << "Balance: $" << accounts_[i].getBalance() << '\n'
              << "Account Number: " << accounts_[i].getAccountNumber() << '\n'
              << "Routing Number: " << accounts_[i].getRoutingNumber() << '\n';
        
        std::cout << '\n';
    }
}

void Client::updateUser(const Client& client) {
    if (client.getFirstName() != "NULL") {
        setFirstName(client.getFirstName());
    }
    if (client.getLastName() != "NULL") {
        setLastName(client.getLastName());
    }
    if (client.getEmail() != "NULL") {
        setEmail(client.getEmail());
    }
    if (client.getPassword() != "NULL") {
        setPassword(client.getPassword());
    }
    if (client.getPin() != -1) {
        updatePin(client.getPin());
    }
}

void Client::updatePin(const int& pin) {
    if (pin < 0 || pin > PIN_LIMIT) {    //6-digit limit for pin number
        std::cout << "Error. Pin Number must be a 4 - 6 digit number." << '\n';
        return;
    }

    pin_ = pin;
}

void Client::updateAccount(const Account& oldAccount, const Account& newAccount) {
    if (!contains(oldAccount.getName())) {
        return;
    }

    for (int i = 0 ; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == oldAccount.getName()) {
            accounts_[i].setName(newAccount.getName());
            accounts_[i].setBalance(newAccount.getBalance());
            accounts_[i].setAccountNumber(newAccount.getAccountNumber());
            accounts_[i].setRoutingNumber(newAccount.getRoutingNumber());
            return;
        }
    }

}

void Client::updateAccounts(const std::vector<Account>& accounts) {
    accounts_ = accounts;
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
            return;
        }
    }
    
}

void Client::updateAccountBalance(const std::string& accountName, const int& amount) {
    for (int i = 0; i < accounts_.size(); ++i) {
        if (accounts_[i].getName() == accountName) {
            accounts_[i].setBalance(amount);
            return;
        }
    }
}

void Client::addAccount(const Account& account) {
    if (contains(account.getName())) {
        std::cout << "Error. \'" << account.getName() << "\' already exists as an account." << '\n';
        return;
    }

    accounts_.push_back(account);
}

void Client::removeAccount(const std::string& accountName) {
    if (!contains(accountName)) {
        std::cout << "Error. \'" << accountName << "\' does not exist as an account." << '\n';
        return;
    }

    std::vector<Account>::iterator it = accounts_.begin();
    for (; it != accounts_.end(); ++it) {
        if (it->getName() == accountName) {
            break;
        }
    }

    if (!it->zeroBalance()) {   //can't close an account that still has money in it
        std::cout << "Error. \'" << it->getName() << "\' does not have a 0 balance! Please zero the account before closing." << '\n';
        return;
    }

    accounts_.erase(it);
}
