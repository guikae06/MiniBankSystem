#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

namespace MiniBank {

class CheckingAccount : public Account {
    double overdraft;
    double fee;

public:
    CheckingAccount(const std::string& id_, const std::string& owner_, double bal = 0.0,
                    double overdraft_ = 200.0, double fee_ = 0.0)
        : Account(id_, owner_, bal), overdraft(overdraft_), fee(fee_) {}

    AccountType getAccountType() const override { return AccountType::Checking; }

    bool withdraw(double amount) override {
        if (balance + overdraft >= amount) {
            balance -= amount;
            balance -= fee;
            return true;
        }
        return false;
    }

    double getOverdraft() const { return overdraft; }
    double getFee() const { return fee; }
};

} // namespace MiniBank

#endif
