#include "menu.h"

Menu::Menu() {
    displayWelcome();

    char exit_ = ' ';
    
    while (exit_ != 'q') {
        if (sys_.getToken().isSignedIn()) {
            displayFullMenu();
            full();
        } else {
            displayStartMenu();
            start();
        }

        std::cout << "Continue? (Enter any key to continue. \'q\' to exit)" << '\n';
        std::cin >> exit_;
        std::cin.ignore();
    }

    displayFarewell();
}

Menu::Menu(const Menu& other) : sys_(other.sys_) {}

Menu::~Menu() {}

Menu& Menu::operator=(const Menu& other) {
    sys_ = other.sys_;
    return *this;
}

void Menu::displayWelcome() const {
    std::cout << "--------------------------------------------------------------------" << '\n';
    std::cout << "Welcome to Cherries Bank System." << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';
    std::cout << '\n';
    std::cout << "Please type in the requested command number followed by pressing \'enter\'." << '\n';
    std::cout << '\n';
}

void Menu::displayFarewell() const {
    std::cout << "Thank you for using Cherries Bank System." << '\n';
    std::cout << "Goodbye." << '\n';
}

void Menu::displayStartMenu() const {
    std::cout << "Main Menu" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';
    std::cout << "1) Sign In" << '\n';
    std::cout << "2) Sign Up" << '\n'; 
    std::cout << "3) Quit" << '\n';
    std::cout << '\n';
}

void Menu::displayFullMenu() const {
    std::cout << "Main Menu" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';
    std::cout << "1) Deposit" << '\n';
    std::cout << "2) Withdrawl" << '\n';
    std::cout << "3) Open Account" << '\n';
    std::cout << "4) Close Account" << '\n';
    std::cout << "5) Update Account" << '\n';
    std::cout << "6) Edit User Profile" << '\n';
    std::cout << "7) Sign out" << '\n';
    std::cout << "8) Quit" << '\n';
    std::cout << '\n';
}

// First System loop
void Menu::start() {
    char input = '_';
    std::cin >> input;
    std::cin.ignore();
    std::cout << '\n';

    switch (input) {
    case '1':
        signIn();
        break;
    case '2':
        signUp();
        break;
    case '3':
        quit();
        break;
    default:
        std::cout << " Please enter a number corresponding to a valid option." << '\n';
        break;
    }
}

// Main System Loop
void Menu::full() {
    char input = '_';
    std::cin >> input;
    std::cin.ignore();
    std::cout << '\n';

    switch (input) {
    case '1':
        deposit();
        break;
    case '2':
        withdrawl();
        break;
    case '3':
        openAccount();
        break;
    case '4':
        closeAccount();
        break;
    case '5':
        updateAccount();
        break;
    case '6':
        editUserProfile();
        break;
    case '7':
        signOut();
        break;
    case '8':
        quit();
        break;
    default:
        std::cout << " Please enter a number corresponding to a valid option." << '\n';
        break;
    }
}

void Menu::signIn() {
    std::string email, password = "";

    std::cout << "Sign In:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Please enter your email: ";
    std::getline(std::cin, email);
    std::cout << '\n';

    std::cout << "Please enter your password: ";
    std::getline(std::cin, password);
    std::cout << '\n';

    sys_.signIn(email, password);

    if (sys_.getToken().isSignedIn()) {
        std::cout << "Welcome back " << sys_.getToken().getCurrentUser().getFullName() << "!" <<  '\n';
    }
}

void Menu::signUp() {
    std::string firstName, lastName, email, password = "";
    int pin = -1;

    std::cout << "Sign Up:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Please enter your first name: ";
    std::getline(std::cin, firstName);
    std::cout << '\n';

    std::cout << "Please enter your last name: ";
    std::getline(std::cin, lastName);
    std::cout << '\n';

    std::cout << "Please enter your email: ";   //future: check to see if email is already taken before proceeding
    std::getline(std::cin, email);
    std::cout << '\n';

    std::cout << "Please enter a password: ";
    std::getline(std::cin, password);
    std::cout << '\n';
    
    std::cout << "Please enter a pin number [4 - 6 digits]: ";
    std::cin >> pin;
    std::cin.ignore();
    std::cout << '\n';

    Client newClient(firstName, lastName, email, password, pin);
    sys_.addCustomer(newClient);
}

void Menu::signOut() {
    sys_.signOut();
}

void Menu::deposit() {
    int pin, amount = 0;

    std::cout << "Deposit:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Please enter your pin: ";
    std::cin >> pin; 
    std::cin.ignore();
    std::cout << '\n';

    if (!sys_.authorize(pin)) {
        return;
    }

    std::string accountName = "";
    std::cout << "Enter the account name you'd like to deposit to: ";
    std::getline(std::cin, accountName);
    std::cout << '\n';

    if (!sys_.getToken().getCurrentUser().contains(accountName)) {
        return;
    }

    std::cout << "How much would you like to deposit? $";
    std::cin >> amount;
    std::cin.ignore();
    std::cout << '\n'; 

    sys_.deposit(pin, accountName, amount);
}

void Menu::withdrawl() {
    int pin, amount = 0;

    std::cout << "Withdrawl:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Please enter your pin: ";
    std::cin >> pin; 
    std::cin.ignore();
    std::cout << '\n';

    if (!sys_.authorize(pin)) {
        return;
    }

    std::string accountName = "";
    std::cout << "Enter the account name you'd like to withdrawl from: ";
    std::getline(std::cin, accountName);
    std::cout << '\n';

    if (!sys_.getToken().getCurrentUser().contains(accountName)) {
        return;
    }

    std::cout << "How much would you like to withdrawl? $";
    std::cin >> amount;
    std::cin.ignore();
    std::cout << '\n'; 

    sys_.withdrawl(pin, accountName, amount);
}

void Menu::openAccount() {
    std::string name = "";

    std::cout << "Open New Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the new account: ";
    std::getline(std::cin, name);
    std::cout << '\n';

    if (sys_.getToken().getCurrentUser().contains(name)) {
        std::cout << name << " already exists as an account." << '\n';
        return;
    }

    Account newAccount(name);

    sys_.addAccount(sys_.getToken().getCurrentUser(), newAccount);
}

void Menu::closeAccount() {
    std::string name = "";

    std::cout << "Close Existing Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the account you'd like to close: ";
    std::getline(std::cin, name);
    std::cout << '\n';

    if (!sys_.getToken().getCurrentUser().contains(name)) {
        return;
    }

    sys_.closeAccount(sys_.getToken().getCurrentUser(), name);
}

void Menu::updateAccount() {
    std::string oldName, newName = "";

    std::cout << "Update Existing Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the account you'd like to edit: ";
    std::getline(std::cin, oldName);
    std::cout << '\n';

    if (!sys_.getToken().getCurrentUser().contains(oldName)) {
        return;
    }

    std::cout << "What would you like to rename " << oldName << "?: ";
    std::getline(std::cin, newName);
    std::cout << '\n';

    sys_.getDatabase().getClient(sys_.getToken().getCurrentUser().getEmail()).getAccount(oldName).setName(newName);
}

void Menu::editUserProfile() {
    // to do
}

void Menu::quit() {
    if (sys_.getToken().isSignedIn()) {
        signOut();
    }
}
