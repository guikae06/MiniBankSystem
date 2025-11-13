#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#pragma once
#include "Account.h"
#include <iostream>

namespace MiniBank {

class CheckingAccount : public Account {
    double overdraftLimit; // maximaal negatief saldo toegestaan
public:
    CheckingAccount(const std::string& accNum, double bal, double limit)
        : Account(accNum, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if(balance - amount < -overdraftLimit) {
            std::cout << "Te veel opname! Limiet overschreden.\n";
        } else {
            balance -= amount;
        }
    }
};

}

#endif // CHECKINGACCOUNT_H
