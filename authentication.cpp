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
    return *this;
}

Client Authentication::getCurrentUser() const {
    return currentUser_;
}

bool Authentication::isSignedIn() const {
    return signedIn_;
}

void Authentication::signIn(const std::string& email, const std::string& password, const Database& database) {
    if (database.contains(email)) {
        if (database.authenticate(email, password)) {
            currentUser_ = database.getClient(email);
            signedIn_ = true;
            return;
        }
    }

    std::cout << "Error. Invalid email or password." << '\n';
}

void Authentication::signOut() {
    Client defaultUser;

    currentUser_ = defaultUser;
    signedIn_ = false;
}
