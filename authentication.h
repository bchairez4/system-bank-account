#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "database.cpp"

class Authentication {
    private:
        Client currentUser_;
        bool signedIn_;
    public:
        Authentication();
        Authentication(const std::string& email, const std::string& password, const Database& database);
        Authentication(const Authentication& other);
        ~Authentication();
        Authentication& operator=(const Authentication& other);
        Client getCurrentUser() const;
        bool isAdmin() const;
        bool isSignedIn() const;
        void signIn(const std::string& email, const std::string& password, const Database& database);
        void signOut();
};

#endif
