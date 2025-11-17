#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

namespace MiniBank {

class SavingsAccount : public Account {
    double interestRate;

public:
    SavingsAccount() : Account(), interestRate(0.01) {}
    SavingsAccount(const std::string& accNum, const std::string& ownerName, double bal = 0.0, double rate = 0.01)
        : Account(accNum, ownerName, bal, /*type*/1), interestRate(rate) {}
    SavingsAccount(const SavingsAccount& other) : Account(other), interestRate(other.interestRate) {}
    ~SavingsAccount() override = default;

    void withdraw(double amount) override {
        if (amount <= 0.0) throw std::invalid_argument("withdraw: amount must be positive");
        if (amount > balance) throw std::runtime_error("SavingsAccount: insufficient funds");
        balance -= amount;
    }

    void addInterest() {
        if (interestRate > 0.0) balance += balance * interestRate;
    }

    double getInterestRate() const { return interestRate; }
    void setInterestRate(double r) { interestRate = r; }
};

} // namespace MiniBank

#endif // SAVINGSACCOUNT_H
