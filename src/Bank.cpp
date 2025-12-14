#include "Bank.h"
#include <fstream>
#include <sstream>

namespace MiniBank {

Bank::Bank() : nextId(1) {}

Bank::~Bank() {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) delete acc;
    accounts.clear();
}

// Account creation
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

// Find account
Account* Bank::findAccount(unsigned int id) const {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto acc : accounts) {
        if (acc->getId() == id) return acc;
    }
    return nullptr;
}

Account* Bank::findByNumber(const std::string& accountNumber) const {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) {
        if(acc->getAccountNumber() == accountNumber) return acc;
    }
    return nullptr;
}

// Users
bool Bank::registerUser(const std::string& username, const std::string& password) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& user : users)
        if (user.username == username)
            return false; // already exists

    // Create account internally
    Account* newAccount = createCheckingAccount(username); // add to accounts internally
    users.push_back({username, password, newAccount->getId()});
    return true;
}


Account* Bank::loginUser(const std::string& username, const std::string& password) const {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& user : users) {
        if (user.username == username && user.password == password)
            return findAccount(user.accountId);
    }
    return nullptr;
}

// Snapshot
std::vector<Account*> Bank::snapshot() const {
    std::lock_guard<std::mutex> lock(mtx);
    return accounts;
}

// Transfer
bool Bank::transfer(Account* from, Account* to, double amount) {
    if(!from || !to) return false;
    if(from->withdraw(amount)) {
        to->deposit(amount);
        return true;
    }
    return false;
}

// Interest
void Bank::payInterest(unsigned int days) {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto acc : accounts) {
        if(auto s = dynamic_cast<SavingsAccount*>(acc))
            s->accrueInterest(days);
    }
}

// Accounts
std::vector<Account*> Bank::getAccounts() const {
    std::lock_guard<std::mutex> lock(mtx);
    return accounts;
}

// StockMarket
StockMarket& Bank::getStockMarket() {
    return stockMarket;
}

// Remove account
void Bank::removeAccount(unsigned int id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::remove_if(accounts.begin(), accounts.end(),
                             [id](Account* acc){ return acc->getId() == id; });
    for(auto itr = it; itr != accounts.end(); ++itr)
        delete *itr;
    accounts.erase(it, accounts.end());
}

// Persistence
bool Bank::saveToFile(const std::string& filename) const {
    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    // Save accounts
    for (auto acc : accounts) {
        out << acc->getId() << " " << acc->getOwnerName() << " " << acc->getBalance() << " " << acc->getAccountNumber() << "\n";

        // Save insurances
        auto ins = acc->getInsurances();
        out << ins.size() << "\n";
        for(auto& i : ins) {
            out << i.name << " " << i.price << "\n";
        }
    }

    // Save users
    out << users.size() << "\n";
    for(auto& u : users) {
        out << u.username << " " << u.password << " " << u.accountId << "\n";
    }

    return true;
}

bool Bank::loadFromFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    for(auto acc : accounts) delete acc;
    accounts.clear();
    users.clear();
    nextId = 1;

    std::string line;
    while (std::getline(in, line)) {
        if(line.empty()) continue;
        std::istringstream iss(line);
        unsigned int id;
        std::string ownerName, accNumber;
        double balance;
        if (!(iss >> id >> ownerName >> balance >> accNumber)) break;

        Account* acc = new CheckingAccount(id, ownerName, balance); // default to CheckingAccount
        accounts.push_back(acc);
        if (id >= nextId) nextId = id + 1;

        // Load insurances
        size_t insCount;
        in >> insCount;
        in.ignore();
        for(size_t j = 0; j < insCount; ++j) {
            std::string insName;
            double insPrice;
            in >> insName >> insPrice;
            acc->buyInsurance(insName, insPrice); // direct add
        }
    }

    // Load users
    size_t userCount;
    in >> userCount;
    in.ignore();
    for(size_t i = 0; i < userCount; ++i) {
        std::string username, password;
        unsigned int accId;
        in >> username >> password >> accId;
        users.push_back({username, password, accId});
    }

    return true;
}

} // namespace MiniBank
