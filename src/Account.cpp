#include "Account.h"
#include <iostream>
#include <algorithm>

namespace MiniBank {

// ---------------------------
// Constructors & Destructor
// ---------------------------
Account::Account() : id(0), ownerName(""), balance(0.0), accountNumber("") {}

Account::Account(unsigned int id, const std::string& owner, double bal)
    : id(id), ownerName(owner), balance(bal)
{
    accountNumber = "ACC" + std::to_string(id);
}

Account::Account(const Account& other)
{
    std::lock_guard<std::mutex> lock(other.mtx);
    id = other.id;
    ownerName = other.ownerName;
    balance = other.balance;
    accountNumber = other.accountNumber;
    insurances = other.insurances;
    history = other.history;
    loans = other.loans;
}

Account::~Account() {}

// ---------------------------
// Deposit & Withdraw
// ---------------------------
void Account::deposit(double amount)
{
    if (amount <= 0) return;
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
    history.push_back({"Deposit", amount});
}

bool Account::withdraw(double amount)
{
    if (amount <= 0) return false;
    std::lock_guard<std::mutex> lock(mtx);
    if (balance >= amount) {
        balance -= amount;
        history.push_back({"Withdrawal", amount});
        return true;
    }
    return false;
}

// ---------------------------
// Loans
// ---------------------------
std::vector<Loan> Account::getLoans() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return loans;
}

void Account::requestLoan(double amount, double interestRate)
{
    if (amount <= 0 || interestRate <= 0) return;
    std::lock_guard<std::mutex> lock(mtx);
    loans.push_back({amount, interestRate});
    balance += amount; // Add loan to account balance
    history.push_back({"Loan received", amount});
}

bool Account::payLoan(int index)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (index < 0 || index >= loans.size()) return false;
    Loan loan = loans[index];
    double totalToPay = loan.amount * (1.0 + loan.interestRate / 100.0);
    if (balance >= totalToPay) {
        balance -= totalToPay;
        loans.erase(loans.begin() + index);
        history.push_back({"Loan paid", totalToPay});
        return true;
    }
    return false;
}

// ---------------------------
// Account info
// ---------------------------
unsigned int Account::getId() const { return id; }
std::string Account::getOwnerName() const { return ownerName; }
double Account::getBalance() const { return balance; }
std::string Account::getAccountNumber() const { return accountNumber; }

// ---------------------------
// Insurance
// ---------------------------
bool Account::buyInsurance(const std::string& name, double price)
{
    if (price <= 0) return false;
    std::lock_guard<std::mutex> lock(mtx);
    if (balance < price) return false;
    balance -= price;
    insurances.push_back({name, price});
    history.push_back({"Insurance", price});
    return true;
}

std::vector<Insurance> Account::getInsurances() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return insurances;
}

// ---------------------------
// Transaction history
// ---------------------------
std::vector<Transaction> Account::getHistory() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return history;
}

// ---------------------------
// Operator=
// ---------------------------
Account& Account::operator=(const Account& other)
{
    if (this == &other) return *this;
    std::lock_guard<std::mutex> lockThis(mtx);
    std::lock_guard<std::mutex> lockOther(other.mtx);

    id = other.id;
    ownerName = other.ownerName;
    balance = other.balance;
    accountNumber = other.accountNumber;
    insurances = other.insurances;
    history = other.history;
    loans = other.loans;
    return *this;
}

} // namespace MiniBank
