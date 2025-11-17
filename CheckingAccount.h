#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

namespace MiniBank {

class CheckingAccount : public Account {
    double overdraftLimit;
    double transactionFee;

public:
    CheckingAccount() : Account(), overdraftLimit(0.0), transactionFee(0.0) {}
    CheckingAccount(const std::string& accNum, const std::string& ownerName, double bal = 0.0, double overdraft = 200.0, double fee = 0.0)
        : Account(accNum, ownerName, bal, /*type*/2), overdraftLimit(overdraft), transactionFee(fee) {}
    CheckingAccount(const CheckingAccount& other)
        : Account(other), overdraftLimit(other.overdraftLimit), transactionFee(other.transactionFee) {}
    ~CheckingAccount() override = default;

    void withdraw(double amount) override {
        if (amount <= 0.0) throw std::invalid_argument("withdraw: amount must be positive");
        double effective = amount + transactionFee;
        if (balance - effective < -overdraftLimit) throw std::runtime_error("CheckingAccount: overdraft limit exceeded");
        balance -= effective;
    }

    double getOverdraftLimit() const { return overdraftLimit; }
    double getTransactionFee() const { return transactionFee; }
    void setOverdraftLimit(double v) { overdraftLimit = v; }
    void setTransactionFee(double f) { transactionFee = f; }
};

} // namespace MiniBank

#endif // CHECKINGACCOUNT_H
