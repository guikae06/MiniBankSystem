#include "Bank.h"
#include <algorithm>

namespace MiniBank {

Bank::Bank() : nextId(1) {}

Bank::~Bank() {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) delete acc;
    accounts.clear();
}

// Create accounts
Account* Bank::createCheckingAccount(const std::string& ownerName, double balance, double overdraft) {
    std::lock_guard<std::mutex> lock(mtx);
    Account* acc = new CheckingAccount(nextId++, ownerName, balance, overdraft);
    accounts.push_back(acc);
    return acc;
}

Account* Bank::createSavingsAccount(const std::string& ownerName, double balance, double interestRate) {
    std::lock_guard<std::mutex> lock(mtx);
    Account* acc = new SavingsAccount(nextId++, ownerName, balance, interestRate);
    accounts.push_back(acc);
    return acc;
}

// Find account by ID
Account* Bank::findAccount(unsigned int id) const {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) {
        if(acc->getId() == id) return acc;
    }
    return nullptr;
}

// Find account by account number
Account* Bank::findByNumber(const std::string& accountNumber) const {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) {
        if(acc->getAccountNumber() == accountNumber)
            return acc;
    }
    return nullptr;
}

// Return copy of account pointers (snapshot)
std::vector<Account*> Bank::snapshot() const {
    std::lock_guard<std::mutex> lock(mtx);
    return accounts;
}

// Transfer money between accounts
bool Bank::transfer(Account* from, Account* to, double amount) {
    if(!from || !to) return false;
    if(from->withdraw(amount)) {
        to->deposit(amount);
        return true;
    }
    return false;
}

// Pay interest on savings accounts
void Bank::payInterest(unsigned int days) {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) {
        if(auto s = dynamic_cast<SavingsAccount*>(acc))
            s->accrueInterest(days);
    }
}

// Return accounts vector
std::vector<Account*> Bank::getAccounts() const {
    std::lock_guard<std::mutex> lock(mtx);
    return accounts;
}

// Get StockMarket
StockMarket& Bank::getStockMarket() {
    return stockMarket;
}

// Remove account by ID
void Bank::removeAccount(unsigned int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::remove_if(accounts.begin(), accounts.end(),
                             [id](Account* acc){ return acc->getId() == id; });
    for(auto itr = it; itr != accounts.end(); ++itr)
        delete *itr;
    accounts.erase(it, accounts.end());
}

} // namespace MiniBank
