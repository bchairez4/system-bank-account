#include "account.h"

#define DEFAULT "CHECKING"
#define EMPTY 0

Account::Account() : name_(DEFAULT), balance_(EMPTY) {
    std::srand((unsigned) time(NULL));

    accountNumber_ = 1 + (std::rand() % 1000000);
    routingNumber_ = 1 + (std::rand()% 1000000);
}

Account::Account(const std::string& name) : name_(name), balance_(EMPTY) {
    std::srand((unsigned) time(NULL));

    accountNumber_ = 1 + (std::rand() % 1000000);
    routingNumber_ = 1 + (std::rand()% 1000000);
}

Account::Account(const std::string& name, const int& balance, const int& accountNumber, const int& routingNumber)
: name_(name), balance_(balance), accountNumber_(accountNumber), routingNumber_(routingNumber) {}

Account::Account(const Account& other)
: name_(other.name_), balance_(other.balance_), accountNumber_(other.accountNumber_), routingNumber_(other.routingNumber_) {}

Account::~Account() {}

Account& Account::operator=(const Account& other) {
    name_ = other.name_;
    balance_ = other.balance_;
    accountNumber_ = other.accountNumber_;
    routingNumber_ = other.routingNumber_;
    return *this;
}

std::string Account::getName() const {
    return name_;
}

bool Account::zeroBalance() const {
    return balance_ == EMPTY;
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
