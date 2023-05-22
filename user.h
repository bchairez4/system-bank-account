#ifndef USER_H
#define USER_H

#include <string>

// Base Class
class User {
    private:
        std::string firstName_;
        std::string lastName_;
        std::string email_;
        std::string password_;
    public:
        User();
        User(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password);
        User(const User& other);
        ~User();
        User& operator=(const User& other);
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getFullName() const;
        std::string getEmail() const;
        std::string getPassword() const;
        void setFirstName(const std::string& firstName);
        void setLastName(const std::string& lastName);
        void setName(const std::string firstName, const std::string lastName);
        void setEmail(const std::string email);
        void setPassword(const std::string password);
};

#endif
