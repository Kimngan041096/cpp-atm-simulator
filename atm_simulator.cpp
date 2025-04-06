#include <iostream>
#include <iomanip> // For setting precision on balance output
#include <vector>  // For account history
#include <string>  // For string manipulation

using namespace std;

// Function Prototypes
void displayMenu();
double checkBalance(double balance);
void deposit(double &balance, double amount, vector<string> &history);
void withdraw(double &balance, double amount, vector<string> &history, double &dailyLimit, double &dailyWithdrawn);
void exitProgram();
bool validateAmount(double amount);
bool validatePIN(string enteredPIN, string correctPIN);
void printTransactionHistory(const vector<string> &history);

int main() {
    double balance = 1000.0;  // Initial balance
    double dailyLimit = 500.0;  // Set a daily withdrawal limit
    double dailyWithdrawn = 0.0; // Track daily withdrawals
    int choice;
    double amount;
    string enteredPIN;
    string correctPIN = "1234";  // Default PIN for the user (you can change this)
    
    vector<string> transactionHistory; // Vector to store transaction history

    // PIN Verification
    cout << "Enter PIN to access your account: ";
    cin >> enteredPIN;

    if (!validatePIN(enteredPIN, correctPIN)) {
        cout << "Incorrect PIN. Access denied!" << endl;
        return 0;
    }

    // Start the ATM simulation
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Check Balance
                cout << "Current Balance: $" << fixed << setprecision(2) << checkBalance(balance) << endl;
                break;
            case 2:
                // Deposit Money
                cout << "Enter deposit amount: $";
                cin >> amount;
                if (validateAmount(amount)) {
                    deposit(balance, amount, transactionHistory);
                    cout << "Deposited: $" << fixed << setprecision(2) << amount << endl;
                } else {
                    cout << "Error: Deposit amount must be non-negative." << endl;
                }
                break;
            case 3:
                // Withdraw Money
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                if (validateAmount(amount)) {
                    withdraw(balance, amount, transactionHistory, dailyLimit, dailyWithdrawn);
                } else {
                    cout << "Error: Withdrawal amount must be non-negative." << endl;
                }
                break;
            case 4:
                // View Transaction History
                printTransactionHistory(transactionHistory);
                break;
            case 5:
                // Exit
                exitProgram();
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function Definitions

// Display the ATM Menu
void displayMenu() {
    cout << "\nWelcome to the ATM\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. View Transaction History\n";
    cout << "5. Exit\n";
}

// Check Balance
double checkBalance(double balance) {
    return balance;
}

// Deposit Money (pass by reference)
void deposit(double &balance, double amount, vector<string> &history) {
    if (amount >= 0) {
        balance += amount;  // Modify the balance by reference
        history.push_back("Deposited: $" + to_string(amount)); // Log the transaction
    }
}

// Withdraw Money (pass by reference)
void withdraw(double &balance, double amount, vector<string> &history, double &dailyLimit, double &dailyWithdrawn) {
    if (amount > balance) {
        cout << "Error: Insufficient funds!" << endl;
    } else if (amount > dailyLimit) {
        cout << "Error: Withdrawal exceeds daily limit of $" << dailyLimit << endl;
    } else if (dailyWithdrawn + amount > dailyLimit) {
        cout << "Error: You have exceeded your daily withdrawal limit of $" << dailyLimit << endl;
    } else if (amount >= 0) {
        balance -= amount;  // Modify the balance by reference
        dailyWithdrawn += amount; // Update daily withdrawal total
        history.push_back("Withdrew: $" + to_string(amount)); // Log the transaction
        cout << "Withdrawal successful: $" << fixed << setprecision(2) << amount << endl;
    }
}

// Exit Program
void exitProgram() {
    cout << "Thank you for using the ATM. Goodbye!" << endl;
}

// Validate that the amount is non-negative
bool validateAmount(double amount) {
    return amount >= 0;
}

// Validate the entered PIN against the correct PIN
bool validatePIN(string enteredPIN, string correctPIN) {
    return enteredPIN == correctPIN;
}

// Print the transaction history
void printTransactionHistory(const vector<string> &history) {
    cout << "\nTransaction History:\n";
    if (history.empty()) {
        cout << "No transactions yet.\n";
    } else {
        for (const string &transaction : history) {
            cout << transaction << endl;
        }
    }
}
