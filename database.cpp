#include "database.h"

#define BANKDATABASE "database.txt"

Database::Database() {
    load(BANKDATABASE);
}

Database::Database(const std::string& fileName) {
    load(fileName);
}

Database::Database(const Database& other) {
    db_ = other.db_;
}

Database::~Database() {}

Database& Database::operator=(const Database& other) {
    db_ = other.db_;
}

std::unordered_map<std::string, Client>::iterator Database::find(const Client& client) {
    std::unordered_map<std::string, Client>::iterator it = db_.find(client.getEmail());
    return it;
}

std::unordered_map<std::string, Client> Database::getDatabase() const {
    return db_;
}

Client Database::getClient(const std::string& email) const {
    std::unordered_map<std::string, Client>::const_iterator it = db_.find(email);

    return it->second;
}

bool Database::authenticate(const std::string& email, const std::string& password) const {
   std::unordered_map<std::string, Client>::const_iterator it = db_.find(email);

    if (it != db_.end()) {
        if (password == it->second.getPassword()) {
            return true;
        }
    }

    return false;
}

bool Database::contains(const std::string& email) const {
    if (db_.empty()) {
        return false;
    }

    if (db_.count(email) > 0) {
        return true;
    }

    return false;
}

void Database::displayTable() const {
    for (std::unordered_map<std::string, Client>::const_iterator it = db_.cbegin(); it != db_.cend(); ++it) {
        std::cout << it->second.getFullName() << " "
                  << it->second.getEmail() << " "
                  << it->second.getPassword() << " "
                  << it->second.getPin() << " ";
        
        std::vector<Account> accounts = it->second.getAccounts();
        for (Account& account : accounts) {
            std::cout << account.getName() << " "
                      << account.getBalance() << " "
                      << account.getAccountNumber() << " "
                      << account.getRoutingNumber() << " ";
        }

        std::cout << '\n';
    }    
}

// Saves the current state of the database to database.txt
void Database::save() {
    std::ofstream file(BANKDATABASE, std::ofstream::out);

    for (std::unordered_map<std::string, Client>::iterator it = db_.begin(); it != db_.end(); ++it) {
        file << it->second.getFirstName() << " "
             << it->second.getLastName() << " "
             << it->second.getEmail() << " "
             << it->second.getPassword() << " "
             << it->second.getPin() << " ";
        
        std::vector<Account> accounts = it->second.getAccounts();
        for (int i = 0; i < accounts.size(); ++i) {
            file << accounts[i].getName() << " "
                 << accounts[i].getBalance() << " "
                 << accounts[i].getAccountNumber() << " " 
                 << accounts[i].getRoutingNumber() << '\n';
        }
    }

    file.close();
}

// Loads a(n existing) database via a given fileName, create file if it doesn't exist
void Database::load(const std::string& fileName) {
    std::ifstream file(fileName, std::ifstream::in);

    if (!file) {
        std::ofstream file(fileName, std::ofstream::out);
    }

    // Skip the actual loading aspect if the file was just created.
    if (file.peek() != file.eof()) {
        while (!file.eof()) {
            std::string firstName, lastName, email, password, accountName = "";
            int pin, balance, accountNumber, routingNumber = 0;
            std::vector<Account> accounts;

            file >> firstName >> lastName >> email >> password >> pin;
            
            while ((file.peek() != '\n') && (file >> accountName)) {
                file >> balance >> accountNumber >> routingNumber;

                Account tempAccount(accountName, balance, accountNumber, routingNumber);
                accounts.push_back(tempAccount);
            }

            Client tempClient(firstName, lastName, email, password, pin, accounts);
            db_.insert({email, tempClient});
        }
    }

    file.close();
}

// Updates a Client's information in the database
void Database::update(const Client& oldClient, const Client& newClient) {
    std::unordered_map<std::string, Client>::iterator it = find(oldClient);

    if (it != db_.end()) {
        db_.erase(it);
        db_.insert({newClient.getEmail(), newClient});
    }
}

// Adds a Client to the database
void Database::add(const Client& client) {
    std::unordered_map<std::string, Client>::iterator it = find(client);

    if (it != db_.end()) {
        return;     //already exists, exit out of function
    }

    db_.insert({client.getEmail(), client});
}

// Removes a Client from the database
void Database::remove(const Client& client) {
    std::unordered_map<std::string, Client>::iterator it = find(client);

    if (it != db_.end()) {
        db_.erase(it);
    }
}
