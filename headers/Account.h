#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <mutex>

namespace MiniBank {

struct Insurance {
    std::string name;
    double price;
};

struct Transaction {
    std::string type; // "Deposit" or "Withdrawal"
    double amount;
};

class Account {
protected:
    unsigned int id;
    std::string ownerName;
    double balance;
    std::string accountNumber;
    std::vector<Insurance> insurances;
    std::vector<Transaction> history; // 🔥 transaction history
    mutable std::mutex mtx;

public:
    Account();
    Account(unsigned int id, const std::string& ownerName, double balance = 0.0);
    Account(const Account& other);
    virtual ~Account();

    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

    unsigned int getId() const;
    std::string getOwnerName() const;
    double getBalance() const;
    std::string getAccountNumber() const;

    bool buyInsurance(const std::string& name, double price);
    std::vector<Insurance> getInsurances() const;

    // 🔥 New: transaction history getter
    std::vector<Transaction> getHistory() const;

    virtual void printInfo() const = 0;

    Account& operator=(const Account& other);
};

} // namespace MiniBank
#endif
