#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

namespace MiniBank {

class Account {
protected:
    std::string accountNumber;  // Uniek nummer van de rekening
    double balance;             // Saldo van de rekening

public:
    // 1. Default constructor
    Account() : accountNumber("000000"), balance(0.0) {}

    // 2. Parameterized constructor
    Account(const std::string& accNum, double bal = 0.0)
        : accountNumber(accNum), balance(bal) {}

    // 3. Copy constructor
    Account(const Account& other)
        : accountNumber(other.accountNumber), balance(other.balance) {}

    // Destructor
    virtual ~Account() {}

    // Functie om geld te storten
    virtual void deposit(double amount) {
        if(amount <= 0) throw std::invalid_argument("Bedrag moet positief zijn!");
        balance += amount;
    }

    // Functie om geld op te nemen – pure virtual
    virtual void withdraw(double amount) = 0;

    // Getters
    const std::string& getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
};

}

#endif // ACCOUNT_H
