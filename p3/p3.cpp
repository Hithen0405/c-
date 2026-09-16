#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
private:
    string owner;
    double balance;

public:
    void openAccount(string name, double initial)
    {
        owner = name;

        if (initial > 0)
        {
            balance = initial;
        }
        else
        {
            balance = 0;
        }
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }

    bool withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            return true;
        }
        else
        {
            return false;
        }
    }

    string getowner()
    {
        return owner;
    }

    double getBalance()
    {
        return balance;
    }
};

int main()
{
    BankAccount account;
    string name;
    double initialDeposit;
    double depositAmount;
    double validwithdrawAmount;

    cout << "Enter account owner's name: ";
    getline(cin, name);

    cout << "Enter initial deposit amount: ";
    cin >> initialDeposit;

    account.openAccount(name, initialDeposit);

    cout << "Enter deposit amount: ";
    cin >> depositAmount;
    account.deposit(depositAmount);

    cout << "\nEnter withdrawal amount: ";
    cin >> validwithdrawAmount;

    if (account.withdraw(validwithdrawAmount))
    {
        cout << "Withdrawal successful" << endl;
    }
    else
    {
        cout << "Withdrawal failed. Insufficient funds." << endl;
    }

    cout << "===== Account Details =====" << endl;
    cout << "Owner: " << account.getowner() << endl;
    cout << "Balance: ₹" << account.getBalance() << endl;

    return 0;
}