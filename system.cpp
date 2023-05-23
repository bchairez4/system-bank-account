#include "system.h"

System::System() {} //null user, false sign in, an empty database (or not)

System::System(const System& other)
: token_(other.token_), database_(other.database_) {}

System::~System() {}

System& System::operator=(const System& other) {
    token_ = other.token_;
    database_ = other.database_;
    return *this;
}

Authentication System::getToken() const{
    return token_;
}

Database System::getDatabase() const {
    return database_;
}

void System::displayUserInfo() const {
    if (token_.isSignedIn()) {
        token_.getCurrentUser().displayUser();
        token_.getCurrentUser().displayAccounts();
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
    //
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
    //
}

void System::deposit(const int& pin, const std::string& accountName, const int& amount) {
    if (!authorize(pin)) {
        return;
    }

    if (!token_.getCurrentUser().contains(accountName)) {
        std::cout << "Error. Account: '\''" << accountName << "'\'' does not exist." << '\n';
        return;
    }

    int new_balance = token_.getCurrentUser().getAccountBalance(accountName) + amount;
    token_.getCurrentUser().updateAccountBalance(accountName, new_balance);
}

void System::withdrawl(const int& pin, const std::string& accountName, const int& amount) {
    if (!authorize(pin)) {
        return;
    }

    if (!token_.getCurrentUser().contains(accountName)) {
        std::cout << "Error. Account: '\''" << accountName << "'\'' does not exist." << '\n';
        return;
    }

    int new_balance = token_.getCurrentUser().getAccountBalance(accountName) - amount;

    if (new_balance >= 0) {
        token_.getCurrentUser().updateAccountBalance(accountName, new_balance);
    }
    
}
