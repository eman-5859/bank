#include <iostream>
#include <string>
using namespace std;

class Bank {
private:
    int accountNumber;
    string* accountHolderName;
    double balance;
    static int noOfAcc;

public:
    Bank() : accountNumber(0), accountHolderName(new string()), balance(0.0) {
        noOfAcc++;
    }

    ~Bank() {
        delete accountHolderName;
        noOfAcc--;
    }

    void createacc() {
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore(); 
        cout << "Enter account holder name: ";
        getline(cin, *accountHolderName);
        cout << "Enter account balance: ";
        cin >> balance;
    }

    static void displayNoOfAcc() {
        cout << "The number of accounts created are: " << noOfAcc << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited: " << amount << " $" << endl;
            cout << "Updated balance: " << balance << " $" << endl;
        }
        else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn: " << amount << " $" << endl;
            cout << "Updated balance: " << balance << " $" << endl;
        }
        else {
            cout << "Insufficient balance." << endl;
        }
    }

    void transfer(Bank& acc2, double amount) {
        if (amount > 0 && amount <= balance) {
            this->withdraw(amount);
            acc2.deposit(amount);
            cout << "$" << amount << " transferred from Account " << accountNumber
                << " to Account " << acc2.accountNumber << "." << endl;
        }
        else {
            cout << "Transfer failed." << endl;
        }
    }

    Bank& operator+(Bank& account1) {
        double amount;
        cout << "Enter the amount to transfer: ";
        cin >> amount;
        this->transfer(account1, amount);
        return *this;
    }

    bool operator==(const Bank& account1) const {
        return balance == account1.balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    friend void display(const Bank& account1);
};


int Bank::noOfAcc = 0;

void display(const Bank& account1) {
    cout << "Account Holder Name: " << *(account1.accountHolderName) << endl;
    cout << "Account Number: " << account1.accountNumber << endl;
    cout << "Account Balance: $" << account1.balance << endl;
}

int main() {
    Bank* account1 = nullptr, * account2 = nullptr;

    int choice;
    int accNum;

    Bank::displayNoOfAcc();

    int action;
    do {
        cout << "Choose an operation: "<<endl;
        cout << "1. Create account" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Transfer" << endl;
        cout << "4. Compare Balances" << endl;
        cout << "5. Display Account Details" << endl;
        cout << "6. Deposit" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> action;

        double amount;
        switch (action) {
        case 1:
            if (!account1) account1 = new Bank();
            if (!account2) account2 = new Bank();
            cout << "Creating Account 1:" << endl;
            account1->createacc();
            cout << "Creating Account 2:" << endl;
            account2->createacc();
            break;

        case 2:
            cout << "Enter the account number to withdraw from: ";
            cin >> accNum;
            if (accNum == account1->getAccountNumber()) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                account1->withdraw(amount);
            }
            else if (accNum == account2->getAccountNumber()) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                account2->withdraw(amount);
            }
            else {
                cout << "Invalid account number." << endl;
            }
            break;

        case 3:
            cout << "From which account you want to transfer:" << endl;
            cout << "1. Account 1 to Account 2" << endl;
            cout << "2. Account 2 to Account 1" << endl;
            cin >> choice;
            if (choice == 1) {
                *account1 + *account2;
            }
            else if (choice == 2) {
                *account2 + *account1;
            }
            else {
                cout << "Invalid transfer choice." << endl;
            }
            break;

        case 4:
            if (*account1 == *account2) {
                cout << "Account balances are the same." << endl;
            }
            else {
                cout << "Account balances are different." << endl;
            }
            break;

        case 5:
            display(*account1);
            display(*account2);
            break;

        case 6:
            cout << "Enter the account number to deposit into: ";
            cin >> accNum;
            if (accNum == account1->getAccountNumber()) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                account1->deposit(amount);
            }
            else if (accNum == account2->getAccountNumber()) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                account2->deposit(amount);
            }
            else {
                cout << "Invalid account number." << endl;
            }
            break;

        case 7:
            cout << "Exiting." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (action != 7);

    delete account1;
    delete account2;

    return 0;
}
