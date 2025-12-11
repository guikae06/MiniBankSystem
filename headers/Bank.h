#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "StockMarket.h"

#include <vector>
#include <mutex>
#include <algorithm>

namespace MiniBank {

class Bank {
private:
    std::vector<Account*> accounts;
    StockMarket stockMarket;
    mutable std::mutex mtx;
    unsigned int nextId;

public:
    Bank();
    ~Bank();

    // Accounts
    Account* createCheckingAccount(const std::string& ownerName, double balance = 0.0, double overdraft = 500.0);
    Account* createSavingsAccount(const std::string& ownerName, double balance = 0.0, double interestRate = 0.03);

    Account* findAccount(unsigned int id) const;
    Account* findByNumber(const std::string& accountNumber) const;
    std::vector<Account*> snapshot() const; // Voor MainWindow GUI

    bool transfer(Account* from, Account* to, double amount);
    void payInterest(unsigned int days);

    std::vector<Account*> getAccounts() const;
    StockMarket& getStockMarket();

    void removeAccount(unsigned int id);
};

} // namespace MiniBank

#endif // BANK_H
