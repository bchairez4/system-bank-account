#include "user.h"

User::User() : firstName_("NULL"), lastName_("NULL"), email_("NULL"), password_("NULL") {}

User::User(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password) 
: firstName_(firstName), lastName_(lastName), email_(email), password_(password) {}

User::User(const User& other) : firstName_(other.firstName_), lastName_(other.lastName_), email_(other.email_), password_(other.password_) {}

User::~User() {}

User& User::operator=(const User& other) {
    firstName_ = other.firstName_;
    lastName_ = other.lastName_;
    email_ = other.email_;
    password_ = other.password_;
    return *this;
}

std::string User::getFirstName() const {
    return firstName_;
}

std::string User::getLastName() const {
    return lastName_;
}

std::string User::getFullName() const {
    return firstName_ + " " + lastName_;
}

std::string User::getEmail() const {
    return email_;
}

std::string User::getPassword() const {
    return password_;
}

void User::setFirstName(const std::string& firstName) {
    if (firstName.empty()) {
        return;
    }

    firstName_ = firstName;
}

void User::setLastName(const std::string& lastName) {
    if (lastName.empty()) {
        return;
    }

    lastName_ = lastName;
}

void User::setFullName(const std::string& firstName, const std::string& lastName) {
    if (firstName.empty() || lastName.empty()) {
        return;
    }

    firstName_ = firstName;
    lastName_ = lastName;
}

void User::setEmail(const std::string& email) {
    if (email.empty()) {
        return;
    }

    email_ = email;
}

void User::setPassword(const std::string& password) {
    if (password.empty()) {
        return;
    }

    password_ = password;
}
