#ifndef MENU_H
#define MENU_H

#include "system.cpp"

class Menu {
    private:
        System sys_;
    public:
        Menu();
        Menu(const Menu& other);
        ~Menu();
        Menu& operator=(const Menu& other);
        void displayWelcome() const;
        void displayFarewell() const;
        void displayStartMenu() const;
        void displayFullMenu() const;
        void start();
        void full();
        void signIn();
        void signUp();
        void signOut();
        void deposit();
        void withdrawl();
        void openAccount();
        void closeAccount();
        void updateAccount();
        void editUserProfile();
        void quit();
};

#endif
