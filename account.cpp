#include "account.h"

#define EMPTY 0

Account::Account() : name_("NULL"), balance_(EMPTY), accountNumber_(EMPTY), routingNumber_(EMPTY) {}

Account::Account(const std::string& name, const int& balance, const int& accountNumber, const int& routingNumber)
: name_(name), balance_(balance), accountNumber_(accountNumber), routingNumber_(routingNumber) {}

Account::Account(const Account& other)
: name_(other.name_), balance_(other.balance_), accountNumber_(other.accountNumber_), routingNumber_(other.routingNumber_) {}

Account::~Account() {}

std::string Account::getName() const {
    return name_;
}

int Account::getBalance() const {
    return balance_;
}
int Account::getAccountNumber() const {
    return accountNumber_;
}

int Account::getRoutingNumber() const {
    return routingNumber_;
}

void Account::setName(const std::string& name) {
    if (name.empty()) {
        return;
    }
    
    name_ = name;
}

void Account::setBalance(const int& balance) {
    balance_ = balance;
}

void Account::setAccountNumber(const int& accountNumber) {
    accountNumber_ = accountNumber;
}

void Account::setRoutingNumber(const int& routingNumber) {
    routingNumber_ = routingNumber;
}

void Account::printBalance() const {
    //std::cout << name_ << " balance: " << '\n';
    //std::cout << "$" << balance_ << '\n';
}
