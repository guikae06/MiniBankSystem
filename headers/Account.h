#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

namespace MiniBank {

enum class AccountType { Checking, Savings };

class Account {
protected:
    std::string id;
    std::string owner;
    double balance;

public:
    Account(const std::string& id_, const std::string& owner_, double bal = 0.0)
        : id(id_), owner(owner_), balance(bal) {}
    virtual ~Account() = default;

    std::string getAccountNumber() const { return id; }
    std::string getOwner() const { return owner; }
    double getBalance() const { return balance; }

    virtual AccountType getAccountType() const = 0;

    virtual void deposit(double amount) { balance += amount; }
    virtual bool withdraw(double amount) { return false; }  // override in Checking
    virtual void addInterest() {}                            // override in Savings
};

std::ostream& operator<<(std::ostream& os, const Account& a);

} // namespace MiniBank

#endif
