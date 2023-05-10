#include "user.h"

User::User() : name_("NULL"), email_("NULL"), password_("NULL") {}

User::User(const std::string& name, const std::string& email, const std::string& password) 
: name_(name), email_(email), password_(password) {}

User::User(const User& other) : name_(other.name_), email_(other.email_), password_(other.password_) {}

User::~User() {}

User& User::operator=(const User& other) {
    name_ = other.name_;
    email_ = other.email_;
    password_ = other.password_;
    return *this;
}

std::string User::getName() const {
    return name_;
}

std::string User::getEmail() const {
    return email_;
}

std::string User::getPassword() const {
    return password_;
}

void User::setName(const std::string fName, const std::string lName) {
    if (fName.empty() || lName.empty()) {
        return;
    }

    name_ = fName + " " + lName;
}

void User::setEmail(const std::string email) {
    if (email.empty()) {
        return;
    }

    email_ = email;
}

void User::setPassword(const std::string password) {
    if (password.empty()) {
        return;
    }

    password_ = password;
}
