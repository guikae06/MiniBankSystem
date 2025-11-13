#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#pragma once
#include "Account.h"
#include <iostream>

namespace MiniBank {

class SavingsAccount : public Account {
    double interestRate; // jaarlijks rentepercentage
public:
    // Constructor
    SavingsAccount(const std::string& accNum, double bal, double rate)
        : Account(accNum, bal), interestRate(rate) {}

    // Implementatie van de pure virtual withdraw functie
    void withdraw(double amount) override {
        if(amount > balance) {
            std::cout << "Niet genoeg saldo om op te nemen!\n";
        } else {
            balance -= amount;
        }
    }

    // Extra functie om rente toe te voegen
    void addInterest() {
        balance += balance * interestRate;
    }
};

}

#endif // SAVINGSACCOUNT_H
