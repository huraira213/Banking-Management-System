
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>


class Account {
private:
    int accountNumber;
    std::string accountHolderName;
    std::string accountType;
    double balance;

public:
    void createAccount(int accNum, std::string name, std::string type, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = name;
        accountType = type;
        balance = initialBalance;
    }

    void displayAccountDetails() const {
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Account Holder Name: " << accountHolderName << "\n";
        std::cout << "Account Type: " << accountType << "\n";
        std::cout << "Balance: $" << balance << "\n";
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds!\n";
        } else {
            balance -= amount;
        }
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }
};

class AccountManagement {
private:
    std::vector<Account> accounts;

public:
    void addAccount(int accNum, std::string name, std::string type, double initialBalance) {
        Account newAccount;
        newAccount.createAccount(accNum, name, type, initialBalance);
        accounts.push_back(newAccount);
        std::cout << "Account created successfully!\n";
    }

    void displayAllAccounts() {
        for (const auto& account : accounts) {
            account.displayAccountDetails();
            std::cout << "-------------------------\n";
        }
    }

    Account* findAccount(int accNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        return nullptr;
    }

    void depositToAccount(int accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account != nullptr) {
            account->deposit(amount);
            std::cout << "Deposit successful. New Balance: $" << account->getBalance() << "\n";
        } else {
            std::cout << "Account not found!\n";
        }
    }

    void withdrawFromAccount(int accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account != nullptr) {
            account->withdraw(amount);
            std::cout << "Updated Balance: $" << account->getBalance() << "\n";
        } else {
            std::cout << "Account not found!\n";
        }
    }

    void transferFunds(int fromAccNum, int toAccNum, double amount) {
        Account* from = findAccount(fromAccNum);
        Account* to = findAccount(toAccNum);
        if (from && to) {
            if (from->getBalance() >= amount) {
                from->withdraw(amount);
                to->deposit(amount);
                std::cout << "Transfer successful!\n";
            } else {
                std::cout << "Insufficient funds!\n";
            }
        } else {
            std::cout << "One or both accounts not found!\n";
        }
    }
};

int main() {
    AccountManagement accountManager;
    int choice;

    do {
        std::cout << "\n=== Banking Management System ===\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Display All Accounts\n";
        std::cout << "3. Deposit\n";
        std::cout << "4. Withdraw\n";
        std::cout << "5. Transfer Funds\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int accNum;
                std::string name, type;
                double balance;
                std::cout << "Enter Account Number(7-digits): ";
                std::cin >> accNum;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ? FIX
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Account Type(current/saving): ";
                std::getline(std::cin, type);
                std::cout << "Enter Initial Balance: ";
                std::cin >> balance;
                accountManager.addAccount(accNum, name, type, balance);
                break;
            }
            case 2:
                accountManager.displayAllAccounts();
                break;
            case 3: {
                int accNum;
                double amount;
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                std::cout << "Enter Amount to Deposit: ";
                std::cin >> amount;
                accountManager.depositToAccount(accNum, amount);
                break;
            }
            case 4: {
                int accNum;
                double amount;
                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                std::cout << "Enter Amount to Withdraw: ";
                std::cin >> amount;
                accountManager.withdrawFromAccount(accNum, amount);
                break;
            }
            case 5: {
                int fromAcc, toAcc;
                double amount;
                std::cout << "Enter Sender Account Number: ";
                std::cin >> fromAcc;
                std::cout << "Enter Receiver Account Number: ";
                std::cin >> toAcc;
                std::cout << "Enter Amount to Transfer: ";
                std::cin >> amount;
                accountManager.transferFunds(fromAcc, toAcc, amount);
                break;
            }
            case 6:
                std::cout << "Exiting system...\n";
                break;
            default:
                std::cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    std::cout << "Thank you for using the Banking Management System!\n";
    return 0;
}
