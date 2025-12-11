#include "CheckingAccount.h"
#include <iostream>

namespace MiniBank {

CheckingAccount::CheckingAccount() : Account(), overdraftLimit(500.0) {}
CheckingAccount::CheckingAccount(unsigned int id, const std::string& ownerName, double balance, double overdraft)
    : Account(id, ownerName, balance), overdraftLimit(overdraft) {}
CheckingAccount::CheckingAccount(const CheckingAccount& other)
    : Account(other), overdraftLimit(other.overdraftLimit) {}
CheckingAccount::~CheckingAccount() {}

bool CheckingAccount::withdraw(double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (balance + overdraftLimit >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void CheckingAccount::printInfo() const {
    std::cout << "Checking Account #" << id << " Owner: " << ownerName
              << " Balance: " << balance << " Overdraft: " << overdraftLimit << "\n";
}

double CheckingAccount::getOverdraftLimit() const { return overdraftLimit; }
void CheckingAccount::setOverdraftLimit(double limit) { overdraftLimit = limit; }

} // namespace MiniBank
