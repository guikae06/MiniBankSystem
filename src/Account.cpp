#include "Account.h"

namespace MiniBank {

Account::Account() : id(0), ownerName(""), balance(0.0), accountNumber("") {}

Account::Account(unsigned int id, const std::string& ownerName, double balance)
    : id(id), ownerName(ownerName), balance(balance)
{
    accountNumber = "ACC" + std::to_string(id); // genereer accountnummer
}

Account::Account(const Account& other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    id = other.id;
    ownerName = other.ownerName;
    balance = other.balance;
    accountNumber = other.accountNumber;
}

Account::~Account() {}

void Account::deposit(double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
}

bool Account::withdraw(double amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

unsigned int Account::getId() const { return id; }
std::string Account::getOwnerName() const { return ownerName; }

double Account::getBalance() const {
    std::lock_guard<std::mutex> lock(mtx);
    return balance;
}

std::string Account::getAccountNumber() const {
    return accountNumber;
}

Account& Account::operator=(const Account& other) {
    if (this != &other) {
        std::lock_guard<std::mutex> lock1(mtx);
        std::lock_guard<std::mutex> lock2(other.mtx);
        id = other.id;
        ownerName = other.ownerName;
        balance = other.balance;
        accountNumber = other.accountNumber;
    }
    return *this;
}

} // namespace MiniBank
