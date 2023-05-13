#include "database.h"

#define BANKDATABASE "database.txt"

Database::Database() {}

Database::Database(const std::string& file) {}

Database::Database(const Database& other) {}

Database::~Database() {}

Database& Database::operator=(const Database& other) {}

void Database::save() {}

void Database::load(const std::string file) {}

void Database::update() {}

void Database::remove() {}
