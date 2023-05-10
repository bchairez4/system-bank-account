#ifndef USER_H
#define USER_H

#include <string>

class User {
    private:
        std::string name_;
        std::string email_;
        std::string password_;
    public:
        User();
        User(const std::string& name, const std::string& email, const std::string& password);
        User(const User& other);
        ~User();
        User& operator=(const User& other);
        std::string getName() const;
        std::string getEmail() const;
        std::string getPassword() const;
        void setName(const std::string fName, const std::string lName);
        void setEmail(const std::string email);
        void setPassword(const std::string password);
};

#endif
