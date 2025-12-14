#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <mutex>

namespace MiniBank {

// ---------------------------
// Insurance and Transaction
// ---------------------------
struct Insurance {
    std::string name;
    double price;
};

struct Transaction {
    std::string type; // "Deposit", "Withdrawal", etc.
    double amount;
};

// ---------------------------
// Loan
// ---------------------------
struct Loan {
    double amount;
    double interestRate; // in percent, e.g., 5.0 = 5%
};

// ---------------------------
// Account base class
// ---------------------------
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

    // ---------------------------
    // Deposit & Withdrawal
    // ---------------------------
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

    // ---------------------------
    // Loans
    // ---------------------------
    std::vector<Loan> getLoans() const;

    void requestLoan(double amount, double interestRate);
    bool payLoan(int index); // pay selected loan if enough balance

    // ---------------------------
    // Account info
    // ---------------------------
    unsigned int getId() const;
    std::string getOwnerName() const;
    double getBalance() const;
    std::string getAccountNumber() const;

    // ---------------------------
    // Insurance
    // ---------------------------
    bool buyInsurance(const std::string& name, double price);
    std::vector<Insurance> getInsurances() const;

    // ---------------------------
    // Transaction history
    // ---------------------------
    std::vector<Transaction> getHistory() const;

    // ---------------------------
    // Abstract
    // ---------------------------
    virtual void printInfo() const = 0;

    // ---------------------------
    // Operator
    // ---------------------------
    Account& operator=(const Account& other);
};

} // namespace MiniBank

#endif // ACCOUNT_H
