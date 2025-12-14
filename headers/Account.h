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
    std::string type;
    double amount;
};

struct Loan {
    double amount;
    double interestRate;
};

class Account {
protected:
    unsigned int id;
    std::string ownerName;
    double balance;
    std::string accountNumber;

    std::vector<Insurance> insurances;
    std::vector<Transaction> history;
    std::vector<Loan> loans;

    mutable std::mutex mtx;

public:
    Account();
    Account(unsigned int id, const std::string& ownerName, double balance = 0.0);
    Account(const Account& other);
    virtual ~Account();

    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

    std::vector<Loan> getLoans() const;
    void requestLoan(double amount, double interestRate);
    bool payLoan(int index);

    unsigned int getId() const;
    std::string getOwnerName() const;
    double getBalance() const;
    std::string getAccountNumber() const;

    bool buyInsurance(const std::string& name, double price);
    std::vector<Insurance> getInsurances() const;
    std::vector<Transaction> getHistory() const;

    virtual void printInfo() const = 0;

    Account& operator=(const Account& other);
};

} // namespace MiniBank

#endif
