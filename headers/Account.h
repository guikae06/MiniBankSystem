#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>
#include <mutex>

namespace MiniBank {

class Account {
protected:
    unsigned int id;
    std::string ownerName;
    double balance;
    mutable std::mutex mtx;
    std::string accountNumber; // uniek accountnummer

public:
    Account();
    Account(unsigned int id, const std::string& ownerName, double balance = 0.0);
    Account(const Account& other);
    virtual ~Account();

    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

    unsigned int getId() const;
    std::string getOwnerName() const;
    double getBalance() const;

    std::string getAccountNumber() const; // toegevoegd

    virtual void printInfo() const = 0;

    Account& operator=(const Account& other);
};

}

#endif // ACCOUNT_H
