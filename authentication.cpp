#include "authentication.h"

Authentication::Authentication() : signedIn_(false) {}

Authentication::Authentication(const std::string& email, const std::string& password, const Database& database) 
: signedIn_(false) {
    signIn(email, password, database);
}

Authentication::Authentication(const Authentication& other) 
: currentUser_(other.currentUser_), signedIn_(other.signedIn_) {}

Authentication::~Authentication() {
    signedIn_ = false;
}

Authentication& Authentication::operator=(const Authentication& other) {
    currentUser_ = other.currentUser_;
    signedIn_ = other.signedIn_;
}

Client Authentication::getCurrentUser() const {
    return currentUser_;
}

bool Authentication::isSignedIn() const {
    return signedIn_;
}

void Authentication::signIn(const std::string& email, const std::string& password, const Database& database) {
    if (database.contains(email)) {
        currentUser_ = database.authenticate(email, password);
        signedIn_ = true;
    }
}

void Authentication::signOff() {
    Client defaultUser;

    currentUser_ = defaultUser;
    signedIn_ = false;
}