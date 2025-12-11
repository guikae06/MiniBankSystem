#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

namespace MiniBank {

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount();
    CheckingAccount(unsigned int id, const std::string& ownerName, double balance, double overdraftLimit = 500.0);
    CheckingAccount(const CheckingAccount& other);
    ~CheckingAccount() override;

    bool withdraw(double amount) override;
    void printInfo() const override;

    double getOverdraftLimit() const;
    void setOverdraftLimit(double limit);
};

}

#endif // CHECKINGACCOUNT_H
