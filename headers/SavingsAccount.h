#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

namespace MiniBank {

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount();
    SavingsAccount(unsigned int id,
                   const std::string& ownerName,
                   double balance,
                   double interestRate = 0.03);
    SavingsAccount(const SavingsAccount& other);
    ~SavingsAccount() override;

    void deposit(double amount) override;
    bool withdraw(double amount) override;

    void accrueInterest(unsigned int days);
    void printInfo() const override;

    double getInterestRate() const;
    void setInterestRate(double rate);
};

}

#endif
