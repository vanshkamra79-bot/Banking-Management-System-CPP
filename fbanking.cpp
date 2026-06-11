#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    char holderName[50];
    long accountNumber;
    double balance;

public:
    void createAccount() {
        cout << "Enter Name : ";
        cin.width(50);
        cin >> holderName;

        accountNumber = (long)time(0) % 900000 + 100000;
        balance = 0.0;

        saveToFile();

        cout << "\nAccount Created Successfully!";
        cout << "\nYour Account Number is: " << accountNumber << endl;
    }

    int loadAccount(long accNo) {
        char filename[40];
        snprintf(filename, sizeof(filename), "acc%ld.txt", accNo);

        ifstream fin(filename);
        if (!fin)
            return 0;

        accountNumber = accNo;
        fin >> holderName >> balance;

        fin.close();
        return 1;
    }

    void saveToFile() {
        char filename[40];
        snprintf(filename, sizeof(filename), "acc%ld.txt", accountNumber);

        ofstream fout(filename);
        fout << holderName << "\n";
        fout << fixed << setprecision(2) << balance << "\n";
        fout.close();
    }

    void deposit() {
        double amount;

        cout << "\nEnter amount to deposit: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "\nInvalid Amount!";
        } else {
            balance += amount;
            saveToFile();
            cout << "\nDeposit Successful!";
        }
    }

    void withdraw() {
        double amount;

        cout << "\nEnter amount to withdraw: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "\nInvalid Amount!";
        } else if (amount > balance) {
            cout << "\nInsufficient Balance!";
        } else {
            balance -= amount;
            saveToFile();
            cout << "\nWithdrawal Successful!";
        }
    }

    void checkBalance() {
        cout << "\n\n===== ACCOUNT DETAILS =====";
        cout << "\nName: " << holderName;
        cout << "\nAccount No: " << accountNumber;
        cout << "\nBalance: " << fixed << setprecision(2) << balance;
        cout << "\n============================";
    }
};

int main() {
    srand((unsigned int)time(0));

    BankAccount acc;
    int option;

    cout << "====== BIGBANK ======\n";
    cout << "1. Create New Account\n";
    cout << "2. Login Existing Account\n";
    cout << "Enter choice: ";
    cin >> option;

    if (option == 1) {
        acc.createAccount();
    } else if (option == 2) {
        long accNo;

        cout << "Enter Account Number: ";
        cin >> accNo;

        if (!acc.loadAccount(accNo)) {
            cout << "\nAccount Not Found!";
            return 0;
        }

        cout << "\nLogin Successful!";
    } else {
        cout << "\nInvalid Option!";
        return 0;
    }

    int choice;

    do {
        cout << "\n\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\n3. Check Balance";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                acc.deposit();
                break;

            case 2:
                acc.withdraw();
                break;

            case 3:
                acc.checkBalance();
                break;

            case 4:
                cout << "\nThank you for using BIGBANK!\n";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 4);

    return 0;
}