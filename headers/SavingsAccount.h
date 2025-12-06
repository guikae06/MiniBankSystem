#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

namespace MiniBank {

class SavingsAccount : public Account {
public:
    SavingsAccount() : Account(), interestRate(0.01) {}
    SavingsAccount(const std::string& id_, const std::string& owner_, double bal = 0.0, double rate = 0.01)
        : Account(id_, owner_, bal), interestRate(rate) {}
    SavingsAccount(const SavingsAccount& other)
        : Account(other), interestRate(other.interestRate) {}
    ~SavingsAccount() override = default;

    AccountType getAccountType() const override { return AccountType::Savings; }

    void addInterest() override {
        balance += balance * interestRate;
    }

    double getInterestRate() const { return interestRate; }

    std::unique_ptr<Account> clone() const override {
        return std::make_unique<SavingsAccount>(*this);
    }

private:
    double interestRate;
};

} // namespace MiniBank

#endif // SAVINGSACCOUNT_H
