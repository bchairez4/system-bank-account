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
    std::unordered_map<std::string, Client>::iterator it = db_.find((client.getPassword() + client.getLastName()));
    return it;
}

std::unordered_map<std::string, Client> Database::getDatabase() const {
    return db_;
}

void Database::displayTable() const {
    for (std::unordered_map<std::string, Client>::const_iterator it = db_.begin(); it != db_.end(); ++it) {
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

// Loads a(n existing) database via a given fileName
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
            db_.insert({(password + lastName), tempClient});
        }
    }

    file.close();
}

// Updates an entry to the database
void Database::update() {
    //
}

// Adds a Client to the database
void Database::add(const Client& client) {
    std::unordered_map<std::string, Client>::iterator it = find(client);

    if (it != db_.end()) {
        return;     //already exists, exit out of function
    }

    db_.insert({(client.getPassword() + client.getLastName()), client});
}

// Removes a Client from the database
void Database::remove(const Client& client) {
    std::unordered_map<std::string, Client>::iterator it = find(client);

    if (it != db_.end()) {
        db_.erase(it);
        return;
    }
}