#include "SavingsAccount.h"
#include <iostream>
#include <cmath>

namespace MiniBank {

SavingsAccount::SavingsAccount() : Account(), interestRate(0.03) {}
SavingsAccount::SavingsAccount(unsigned int id, const std::string& ownerName, double balance, double rate)
    : Account(id, ownerName, balance), interestRate(rate) {}
SavingsAccount::SavingsAccount(const SavingsAccount& other)
    : Account(other), interestRate(other.interestRate) {}
SavingsAccount::~SavingsAccount() {}

void SavingsAccount::deposit(double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
}

bool SavingsAccount::withdraw(double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void SavingsAccount::accrueInterest(unsigned int days) {
    std::lock_guard<std::mutex> lock(mtx);
    double dailyRate = interestRate / 365.0;
    balance *= std::pow(1.0 + dailyRate, days);
}

void SavingsAccount::printInfo() const {
    std::cout << "Savings Account #" << id << " Owner: " << ownerName
              << " Balance: " << balance << " Interest Rate: " << interestRate << "\n";
}

double SavingsAccount::getInterestRate() const { return interestRate; }
void SavingsAccount::setInterestRate(double rate) { interestRate = rate; }

} // namespace MiniBank
