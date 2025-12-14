#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "StockMarket.h"

#include <vector>
#include <mutex>
#include <string>

namespace MiniBank {

struct User {
    std::string username;
    std::string password; // For simplicity, store plaintext (hash in real system)
    unsigned int accountId;
};

class Bank {
private:
    std::vector<Account*> accounts;
    std::vector<User> users;
    StockMarket stockMarket;
    mutable std::mutex mtx;
    unsigned int nextId;

public:
    Bank();
    ~Bank();

    // Account creation
    Account* createCheckingAccount(const std::string& ownerName, double balance = 0.0, double overdraft = 500.0);
    Account* createSavingsAccount(const std::string& ownerName, double balance = 0.0, double interestRate = 0.03);

    // Find account
    Account* findAccount(unsigned int id) const;
    Account* findByNumber(const std::string& accountNumber) const;

    // Users
    bool registerUser(const std::string& username, const std::string& password);
    Account* loginUser(const std::string& username, const std::string& password) const;

    std::vector<Account*> snapshot() const; // For GUI

    // Transfer
    bool transfer(Account* from, Account* to, double amount);
    void payInterest(unsigned int days);

    std::vector<Account*> getAccounts() const;
    StockMarket& getStockMarket();

    void removeAccount(unsigned int id);

    // Persistence
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

} // namespace MiniBank

#endif
