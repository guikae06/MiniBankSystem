#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ostream>
#include <stdexcept>

namespace MiniBank {

using uint8 = unsigned char;

class Account {
protected:
    std::string accountNumber;
    std::string owner;
    double balance;
    uint8 accountType{0};

public:
    Account() : accountNumber("000000"), owner("unknown"), balance(0.0), accountType(0) {}
    Account(const std::string& accNum, const std::string& ownerName, double bal = 0.0, uint8 type = 0)
        : accountNumber(accNum), owner(ownerName), balance(bal), accountType(type) {}
    Account(const Account& other)
        : accountNumber(other.accountNumber), owner(other.owner), balance(other.balance), accountType(other.accountType) {}

    virtual ~Account() = default;

    virtual void deposit(double amount) {
        if (amount <= 0.0) throw std::invalid_argument("deposit: amount must be positive");
        this->balance += amount;
    }

    virtual void withdraw(double amount) = 0; // abstract

    inline const std::string& getAccountNumber() const { return accountNumber; }
    inline const std::string& getOwner() const { return owner; }
    inline double getBalance() const { return balance; }
    inline uint8 getAccountType() const { return accountType; }

    void setOwner(const std::string& newOwner) {
        if (newOwner.empty()) throw std::invalid_argument("owner cannot be empty");
        owner = newOwner;
    }

    // Print helper - declared here, defined in Account.cpp
    friend std::ostream& operator<<(std::ostream& os, const Account& a);
};

} // namespace MiniBank

#endif // ACCOUNT_H
