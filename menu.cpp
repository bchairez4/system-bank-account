#include "menu.h"

#define INPUT_IGNORE 100

Menu::Menu() {
    displayWelcome();

    char exit_ = ' ';
    
    while (exit_ != 'q') {
        if (sys_.getToken().isSignedIn()) {
            displayFullMenu();
            exit_ = full();
        } else {
            displayStartMenu();
            exit_ = start();
        }
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
    std::cout << "3) Display Accounts" << '\n';
    std::cout << "4) Open Account" << '\n';
    std::cout << "5) Close Account" << '\n';
    std::cout << "6) Update Account" << '\n';
    std::cout << "7) Edit User Profile" << '\n';
    std::cout << "8) Sign out" << '\n';
    std::cout << "9) Quit" << '\n';
    std::cout << '\n';
}

// First System loop
char Menu::start() {
    char input = '_';
    std::cin.get(input);
    std::cin.ignore(INPUT_IGNORE, '\n');
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
        return 'q';
        break;
    default:
        std::cout << " Please enter a number corresponding to a valid option." << '\n';
        break;
    }

    return ' ';
}

// Main System Loop
char Menu::full() {
    char input = '_';
    std::cin.get(input);
    std::cin.ignore(INPUT_IGNORE, '\n');
    std::cout << '\n';

    switch (input) {
    case '1':
        deposit();
        break;
    case '2':
        withdrawl();
        break;
    case '3':
        displayAccounts();
        break;
    case '4':
        openAccount();
        break;
    case '5':
        closeAccount();
        break;
    case '6':
        updateAccount();
        break;
    case '7':
        editUserProfile();
        break;
    case '8':
        signOut();
        break;
    case '9':
        quit();
        return 'q';
        break;
    default:
        std::cout << " Please enter a number corresponding to a valid option." << '\n';
        break;
    }

    return ' ';
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

    std::cout << "Please enter your email: ";
    std::getline(std::cin, email);
    std::cout << '\n';

    if (sys_.contains(email)) {
        char response = ' ';
        std::cout << "Error. Account is associated with an account. Sign in? [y or n]: ";
        std::cin >> response;
        std::cin.ignore(INPUT_IGNORE, '\n');
        std::cout << '\n';

        if (response == 'y') {
            signIn();
            return;
        }

        while (sys_.contains(email)) {
            std::cout << "Please enter a vaild email: ";
            std::getline(std::cin, email);
            std::cout << '\n';
        }
    }

    std::cout << "Please enter a password: ";
    std::getline(std::cin, password);
    std::cout << '\n';
    
    std::cout << "Please enter a pin number [4 - 6 digits]: ";
    std::cin >> pin;
    std::cin.ignore();
    std::cout << '\n';

    if (pin < 0 || pin > PIN_LIMIT) {
        while (pin < 0 || pin > PIN_LIMIT) {
            std::cout << "Error. Pin number must be 4 - 6 digits long." << '\n';
            std::cout << "Please enter a pin number [4 - 6 digits]: ";
            std::cin >> pin;
            std::cin.ignore();
            std::cout << '\n';
        }
    }

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
        std::cout << "Error. \'" << accountName << "\' does not exist as an account." << '\n';
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
        std::cout << "Error. \'" << accountName << "\' does not exist as an account." << '\n';
        return;
    }

    std::cout << "Current balance: $" << sys_.getToken().getCurrentUser().getAccountBalance(accountName) << '\n';
    std::cout << "How much would you like to withdrawl? $";
    std::cin >> amount;
    std::cin.ignore();
    std::cout << '\n'; 

    sys_.withdrawl(pin, accountName, amount);
}

void Menu::displayAccounts() const {
    std::cout << "Display Accounts:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    sys_.displayUserInfo();
}

void Menu::openAccount() {
    std::string name = "";

    std::cout << "Open New Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the new account: ";
    std::getline(std::cin, name);
    std::cout << '\n';

    Account newAccount(name);

    sys_.addAccount(sys_.getToken().getCurrentUser(), newAccount);

    std::cout << "Success! Added \'" << name << "\' to your accounts." << '\n'; 
}

void Menu::closeAccount() {
    std::string name = "";

    std::cout << "Close Existing Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the account you'd like to close: ";
    std::getline(std::cin, name);
    std::cout << '\n';

    sys_.closeAccount(sys_.getToken().getCurrentUser(), name);

    std::cout << "Success! Removed \'" << name << "\' from your accounts." << '\n'; 
}

void Menu::updateAccount() {
    std::string oldName, newName = "";

    std::cout << "Update Existing Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the account you'd like to edit: ";
    std::getline(std::cin, oldName);
    std::cout << '\n';

    if (!sys_.getToken().getCurrentUser().contains(oldName)) {
        std::cout << "Error. \'" << oldName << "\' does not exist as an account." << '\n';
        return;
    }

    std::cout << "What would you like to rename " << oldName << "?: ";
    std::getline(std::cin, newName);
    std::cout << '\n';

    Account oldAccount = sys_.getToken().getCurrentUser().getAccount(oldName);
    Account newAccount = oldAccount;
    newAccount.setName(newName);

    sys_.updateCustomerAccount(sys_.getToken().getCurrentUser(), oldAccount, newAccount);
}

void Menu::editUserProfile() {
    std::string firstName, lastName, password = "";
    Client newClient;

    std::cout << "Edit User Profile:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter your new First Name: (Press \'enter\' to skip)" << '\n';
    std::getline(std::cin, firstName);
    std::cout << '\n';

    std::cout << "Enter your new Last Name: (Press \'enter\' to skip)";
    std::getline(std::cin, lastName);
    std::cout << '\n';

    std::cout << "Enter your new Password: (Press \'enter\' to skip)";
    std::getline(std::cin, password);
    std::cout << '\n';

    if (!firstName.empty()) {
        newClient.setFirstName(firstName);
    }
    if (!lastName.empty()) {
        newClient.setLastName(lastName);
    }
    if (!password.empty()) {
        newClient.setPassword(password);
    }

    sys_.updateCustomer(sys_.getToken().getCurrentUser(), newClient);
}

void Menu::quit() {
    if (sys_.getToken().isSignedIn()) {
        signOut();
    }
}
