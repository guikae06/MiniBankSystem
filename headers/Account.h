#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <memory>
#include <stdexcept>

namespace MiniBank {

enum class AccountType : unsigned char { Checking = 0, Savings = 1 };

class Account {
public:
    Account() : id(""), owner(""), balance(0.0) {}
    Account(const std::string& id_, const std::string& owner_, double bal = 0.0)
        : id(id_), owner(owner_), balance(bal) {}
    Account(const Account& other) : id(other.id), owner(other.owner), balance(other.balance) {}
    virtual ~Account() = default;

    std::string getAccountNumber() const { return id; }
    std::string getOwner() const { return owner; }
    double getBalance() const { return balance; }

    virtual AccountType getAccountType() const = 0;

    virtual void deposit(double amount) {
        if (amount < 0) throw std::invalid_argument("deposit negative");
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount < 0) throw std::invalid_argument("withdraw negative");
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    virtual void addInterest() {}

    virtual std::unique_ptr<Account> clone() const = 0;

protected:
    std::string id;
    std::string owner;
    double balance;
};

} // namespace MiniBank

#endif // ACCOUNT_H
