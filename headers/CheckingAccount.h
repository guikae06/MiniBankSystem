#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"
#include <stdexcept>

namespace MiniBank {

class CheckingAccount : public Account {
public:
    CheckingAccount() : Account(), overdraft(0.0), fee(0.0) {}
    CheckingAccount(const std::string& id_, const std::string& owner_, double bal = 0.0,
                    double overdraft_ = 200.0, double fee_ = 0.0)
        : Account(id_, owner_, bal), overdraft(overdraft_), fee(fee_) {}
    CheckingAccount(const CheckingAccount& other)
        : Account(other), overdraft(other.overdraft), fee(other.fee) {}
    ~CheckingAccount() override = default;

    AccountType getAccountType() const override { return AccountType::Checking; }

    bool withdraw(double amount) override {
        if (amount < 0) throw std::invalid_argument("withdraw negative");
        if (balance + overdraft >= amount) {
            balance -= amount;
            if (fee != 0.0) balance -= fee;
            return true;
        }
        return false;
    }

    double getOverdraft() const { return overdraft; }
    double getFee() const { return fee; }

    std::unique_ptr<Account> clone() const override {
        return std::make_unique<CheckingAccount>(*this);
    }

private:
    double overdraft;
    double fee;
};

} // namespace MiniBank

#endif // CHECKINGACCOUNT_H
