#include "menu.h"

#define INPUT_IGNORE 100

Menu::Menu() {
    displayWelcome();

    char exit_ = ' ';
    
    while (exit_ != 'q') {
        if (sys_.isSignedInCustomer()) {
            if (sys_.isSignedInAdmin()) {
                displayAdminMenu();
                exit_ = admin();
            } else {
                displayFullMenu();
                exit_ = full();
            }
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

void Menu::displayAdminMenu() const {
    std::cout << "Main Menu" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';
    std::cout << "1) Display Database" << '\n';
    std::cout << "2) Add User" << '\n'; 
    std::cout << "3) Remove User" << '\n';
    std::cout << "4) Sign Out" << '\n'; 
    std::cout << "5) Quit" << '\n';
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
    char input = ' ';
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

// Admin System loop
char Menu::admin() {
    char input = ' ';
    std::cin.get(input);
    std::cin.ignore(INPUT_IGNORE, '\n');
    std::cout << '\n';

    switch(input) {
        case '1':
            displayDatabase();
            break;
        case '2':
            addCustomer();
            break;
        case '3':
            removeCustomer();
            break;
        case '4':
            signOut();
            break;
        case '5':
            return 'q';
            break;
        default:
            std::cout << " Please enter a number corresponding to a valid option." << '\n';
            break;
    }

    return ' ';
}

// Main System loop
char Menu::full() {
    char input = ' ';
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
        if (sys_.getToken().isAdmin()) {
            std::cout << "Welcome Admin." << '\n';
            return;
        }

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

void Menu::displayDatabase() const {
    std::cout << "Display Database:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    sys_.displayDatabase();
    std::cout << '\n';
}

void Menu::addCustomer() {
    std::string firstName, lastName, email, password, accountName = "";
    int pin, balance, numAccounts = 0;

    std::cout << "Add Customer:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Please enter the customer's first name: ";
    std::getline(std::cin, firstName);
    std::cout << '\n';

    std::cout << "Please enter the customer's last name: ";
    std::getline(std::cin, lastName);
    std::cout << '\n';

    std::cout << "Please enter the customer's email: ";
    std::getline(std::cin, email);
    std::cout << '\n';

    if (sys_.contains(email)) {
        char response = ' ';
        std::cout << "Error. Account is associated with an account. Exit Add Customer? [y or n]: ";
        std::cin >> response;
        std::cin.ignore(INPUT_IGNORE, '\n');
        std::cout << '\n';

        if (response == 'y') {
            return;
        }

        while (sys_.contains(email)) {
            std::cout << "Please enter a different email: ";
            std::getline(std::cin, email);
            std::cout << '\n';
        }
    }

    std::cout << "Please enter the customer's password: ";
    std::getline(std::cin, password);
    std::cout << '\n';

    std::cout << "Please enter the customer's pin number [4 - 6 digits]: ";
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

    std::vector<Account> accounts;
    std::cout << "How many accounts is the customer opening?: ";
    std::cin >> numAccounts;
    std::cin.ignore();
    std::cout << '\n';

    for (int i = 0; i < numAccounts; ++i) {
        std::cout << "Enter the name for account #" << i+1 << ": ";
        std::getline(std::cin, accountName);
        std::cout << '\n';

        std::cout << "Initial deposit? $";
        std::cin >> balance;
        std::cin.ignore();
        std::cout << '\n';

        Account tempAccount(accountName, balance);
        accounts.push_back(tempAccount);
    }

    Client newClient(firstName, lastName, email, password, pin, accounts);

    sys_.addCustomer(newClient);

    std::cout << "Successfully added " << firstName << "." << '\n';
}

void Menu::removeCustomer() {
    std::string email = "";

    std::cout << "Remove Customer:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Please enter the email of the customer you wish to erase from the system: ";
    std::getline(std::cin, email);
    std::cout << '\n';

    if (!sys_.contains(email)) {
        std::cout << "Error. \'" << email << "\' does not exist as a customer in the database." << '\n';
        return;
    }

    Client tempClient("NULL", "NULL", email, "NULL", 0);

    sys_.removeCustomer(tempClient);

    std::cout << "Successfully removed " << email << "." << '\n';
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

    if (!sys_.containsCustomerAccount(sys_.getToken().getCurrentUser(), accountName)) {
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

    if (!sys_.containsCustomerAccount(sys_.getToken().getCurrentUser(), accountName)) {
        std::cout << "Error. \'" << accountName << "\' does not exist as an account." << '\n';
        return;
    }

    std::cout << "Current balance: $" << sys_.getCustomerAccountBalance(sys_.getToken().getCurrentUser(), accountName) << '\n';
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
    std::string accountName = "";

    std::cout << "Close Existing Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the account you'd like to close: ";
    std::getline(std::cin, accountName);
    std::cout << '\n';

    if (!sys_.containsCustomerAccount(sys_.getToken().getCurrentUser(), accountName)) {
        std::cout << "Error. \'" << accountName << "\' does not exist as an account." << '\n';
        return;
    }

    if (sys_.closeAccount(sys_.getToken().getCurrentUser(), accountName)) {
        std::cout << "Success! Removed \'" << accountName << "\' from your accounts." << '\n';
    }
}

void Menu::updateAccount() {
    std::string oldAccountName, newAccountName = "";

    std::cout << "Update Existing Account:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter the name of the account you'd like to edit: ";
    std::getline(std::cin, oldAccountName);
    std::cout << '\n';

    if (!sys_.containsCustomerAccount(sys_.getToken().getCurrentUser(), oldAccountName)) {
        std::cout << "Error. \'" << oldAccountName << "\' does not exist as an account." << '\n';
        return;
    }

    std::cout << "What would you like to rename " << oldAccountName << "?: ";
    std::getline(std::cin, newAccountName);
    std::cout << '\n';

    Account oldAccount = sys_.getCustomerAccount(sys_.getToken().getCurrentUser(), oldAccountName);
    Account newAccount = oldAccount;
    newAccount.setName(newAccountName);

    sys_.updateCustomerAccount(sys_.getToken().getCurrentUser(), oldAccount, newAccount);

    std::cout << "Successfully updated " << newAccountName << "." << '\n';
}

void Menu::editUserProfile() {
    std::string firstName, lastName, password = "";
    int pin = -1;
    Client newClient;

    std::cout << "Edit User Profile:" << '\n';
    std::cout << "--------------------------------------------------------------------" << '\n';

    std::cout << "Enter your new First Name (Press \'enter\' to skip): ";
    std::getline(std::cin, firstName);
    std::cout << '\n';

    std::cout << "Enter your new Last Name (Press \'enter\' to skip): ";
    std::getline(std::cin, lastName);
    std::cout << '\n';

    std::cout << "Enter your new Password (Press \'enter\' to skip): ";
    std::getline(std::cin, password);
    std::cout << '\n';

    std::cout << "Enter your new Pin Number (Enter \'-1\' to skip): ";
    std::cin >> pin;
    std::cin.ignore();
    std::cout << '\n';

    if (pin > PIN_LIMIT) {
        while (pin > PIN_LIMIT) {
            std::cout << "Error. Pin number must be 4 - 6 digits long." << '\n';
            std::cout << "Please enter a pin number [4 - 6 digits]: (Enter \'-1\' to skip): ";
            std::cin >> pin;
            std::cin.ignore();
            std::cout << '\n';
        }
    }

    if (!firstName.empty()) {
        newClient.setFirstName(firstName);
    }
    if (!lastName.empty()) {
        newClient.setLastName(lastName);
    }
    if (!password.empty()) {
        newClient.setPassword(password);
    }
    if (pin != -1) {
        newClient.updatePin(pin);
    }

    sys_.updateCustomer(sys_.getToken().getCurrentUser(), newClient);

    std::cout << "Successfully updated account." << '\n';
}

void Menu::quit() {
    if (sys_.getToken().isSignedIn()) {
        signOut();
    }
}

