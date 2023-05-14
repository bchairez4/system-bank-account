#ifndef DATABASE_H
#define DATABASE_H

#include "client.cpp"
#include <unordered_map>
#include <fstream>

// Key is a string comprised of a concatonation of Client's password and last name. (In theory, both should be unique enough to almost never cause collisions.) 
// Value is the Client object containing all pertinent data.

class Database {
    private:
        std::unordered_map<std::string, Client> db_;
    public:
        Database();
        Database(const std::string& file);
        Database(const Database& other);
        ~Database();
        Database& operator=(const Database& other);
        std::unordered_map<std::string, Client>::iterator find(const Client& client);
        std::unordered_map<std::string, Client> getDatabase() const;
        void displayTable() const;
        void save();
        void load(const std::string& file);
        void update();
        void add(const Client& client);
        void remove(const Client& client);
};

#endif
