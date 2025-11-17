#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

namespace MiniBank {

class SavingsAccount : public Account {
    double interestRate;

public:
    SavingsAccount(const std::string& id_, const std::string& owner_, double bal = 0.0,
                   double rate = 0.01)
        : Account(id_, owner_, bal), interestRate(rate) {}

    AccountType getAccountType() const override { return AccountType::Savings; }

    void addInterest() override {
        balance += balance * interestRate;
    }
};

} // namespace MiniBank

#endif
