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

class Account {
protected:
    unsigned int id;
    std::string ownerName;
    double balance;
    std::string accountNumber;
    std::vector<Insurance> insurances;
    mutable std::mutex mtx;

public:
    Account();
    Account(unsigned int id, const std::string& ownerName, double balance = 0.0);
    Account(const Account& other);
    virtual ~Account();

    // 🔥 MOET VIRTUAL ZIJN
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);

    unsigned int getId() const;
    std::string getOwnerName() const;
    double getBalance() const;
    std::string getAccountNumber() const;

    bool buyInsurance(const std::string& name, double price);
    std::vector<Insurance> getInsurances() const;

    virtual void printInfo() const = 0;

    Account& operator=(const Account& other);
};

} // namespace MiniBank

#endif
