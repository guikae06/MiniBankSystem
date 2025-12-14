#include "Account.h"

namespace MiniBank {

Account::Account()
    : id(0), ownerName(""), balance(0.0), accountNumber("") {}

Account::Account(unsigned int id, const std::string& ownerName, double balance)
    : id(id), ownerName(ownerName), balance(balance)
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
}

Account::~Account() {}

void Account::deposit(double amount)
{
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
}

bool Account::withdraw(double amount)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

unsigned int Account::getId() const { return id; }
std::string Account::getOwnerName() const { return ownerName; }

double Account::getBalance() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return balance;
}

std::string Account::getAccountNumber() const
{
    return accountNumber;
}

// 🔥 BUY INSURANCE
bool Account::buyInsurance(const std::string& name, double price)
{
    std::lock_guard<std::mutex> lock(mtx);

    if (balance < price)
        return false;

    balance -= price;
    insurances.push_back({name, price});
    return true;
}

std::vector<Insurance> Account::getInsurances() const
{
    std::lock_guard<std::mutex> lock(mtx);
    return insurances;
}

Account& Account::operator=(const Account& other)
{
    if (this != &other) {
        std::scoped_lock lock(mtx, other.mtx);
        id = other.id;
        ownerName = other.ownerName;
        balance = other.balance;
        accountNumber = other.accountNumber;
        insurances = other.insurances;
    }
    return *this;
}

} // namespace MiniBank
