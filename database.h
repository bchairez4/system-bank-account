#ifndef DATABASE_H
#define DATABASE_H

#include "client.cpp"
#include <unordered_map>
#include <fstream>

class Database {
    private:
        std::unordered_map<std::string, Client> db_;
    public:
        Database();
        Database(const std::string& file);
        Database(const Database& other);
        ~Database();
        Database& operator=(const Database& other);
        void save();
        void load(const std::string file);
        void update();
        void remove();
};

#endif
