#include "system.h"

System::System() {}

System::System(const System& other)
: token_(other.token_), database_(other.database_) {}

System::~System() {}

System& System::operator=(const System& other) {
    token_ = other.token_;
    database_ = other.database_;
    return *this;
}

Authentication System::getToken() const {
    return token_;
}

Database System::getDatabase() const {
    return database_;
}

void System::displayUserInfo() const {
    if (token_.isSignedIn()) {
        database_.getClient(token_.getCurrentUser().getEmail()).displayUser();
        database_.getClient(token_.getCurrentUser().getEmail()).displayAccounts();
    }
}

void System::displayDatabase() const {
    database_.displayTable();
}

bool System::authorize(const int& pin) const {
    if (token_.isSignedIn()) {
        if (pin == token_.getCurrentUser().getPin()) {
            return true;
        }
    }

    std::cout << "Error. Invalid pin." << '\n';
    return false;
}

bool System::contains(const std::string& email) const {
    return database_.contains(email);
}

void System::signIn(const std::string& email, const std::string& password) {
    if (!token_.isSignedIn()) {
        token_.signIn(email, password, database_);
    }
}

void System::signOut() {
    token_.signOut();
}

void System::addCustomer(const Client& client) {
    database_.add(client);
}

void System::removeCustomer(const Client& client) {
    database_.remove(client);
}

void System::updateCustomer(const Client& oldClient, const Client& newClient) {
    if (!token_.isSignedIn()) {
        return;
    }

    std::unordered_map<std::string, Client>::iterator it = database_.find(oldClient);

    if (it != database_.getDatabase().end()) {
        it->second.updateUser(newClient);
    }
}

void System::addAccount(const Client& client, const Account& account) {
    std::unordered_map<std::string, Client>::iterator it = database_.find(client);

    if (it != database_.getDatabase().end()) {
        it->second.addAccount(account);
    }
}

void System::closeAccount(const Client& client, const std::string& accountName) {
    std::unordered_map<std::string, Client>::iterator it = database_.find(client);

    if (it != database_.getDatabase().end()) {
        it->second.removeAccount(accountName);
    }
}

void System::updateCustomerAccount(const Client& client, const Account& oldAccount, const Account& newAccount) {
    if (!database_.contains(client.getEmail())) {
        std::cout << "Error. \'" << client.getFullName() << "\' does not exist in the database." << '\n';
        return;
    }

    std::unordered_map<std::string, Client>::iterator it = database_.find(client);

    if (it != database_.getDatabase().end()) {
        it->second.updateAccount(oldAccount, newAccount);
    }
}

int System::getCustomerAccountBalance(const Client& client, const std::string& accountName) const {
    return database_.getClient(client.getEmail()).getAccountBalance(accountName);
}

void System::deposit(const int& pin, const std::string& accountName, const int& amount) {
    if (!database_.contains(token_.getCurrentUser().getEmail())) {
        std::cout << "Error. \'" << token_.getCurrentUser().getFullName() << "\' does not exist in the database." << '\n';
        return;
    }

    if (!token_.getCurrentUser().contains(accountName)) {
        return;
    }

    std::unordered_map<std::string, Client>::iterator it = database_.find(token_.getCurrentUser());

    if (it != database_.getDatabase().end()) {
        int newBalance = it->second.getAccountBalance(accountName) + amount;
        it->second.updateAccountBalance(accountName, newBalance);
        std::cout << "Success. Deposited $" << amount << '\n';
        std::cout << "New Balance: $" << it->second.getAccountBalance(accountName) << '\n';
    }
}

void System::withdrawl(const int& pin, const std::string& accountName, const int& amount) {
    if (!database_.contains(token_.getCurrentUser().getEmail())) {
        std::cout << "Error. \'" << token_.getCurrentUser().getFullName() << "\' does not exist in the database." << '\n';
        return;
    }

    if (!token_.getCurrentUser().contains(accountName)) {
        return;
    }

    std::unordered_map<std::string, Client>::iterator it = database_.find(token_.getCurrentUser());

    if (it != database_.getDatabase().end()) {
        int newBalance = it->second.getAccountBalance(accountName) - amount;

        if (newBalance >= 0) {
            it->second.updateAccountBalance(accountName, newBalance);
            std::cout << "Success. Received $" << amount << '\n';
            std::cout << "New Balance: $" << it->second.getAccountBalance(accountName) << '\n';
            return;
        }

        std::cout << "Error. Trying to withdrawl more than what is available." << '\n';
    }
}
