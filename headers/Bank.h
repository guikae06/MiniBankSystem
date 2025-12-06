#ifndef BANK_H
#define BANK_H

#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <thread>
#include <atomic>
#include "Account.h"

namespace MiniBank {

class Bank {
public:
    Bank() = default;
    Bank(const Bank& other) {
        std::lock_guard<std::mutex> lock(other.mtx);
        for (const auto& a : other.accounts) if (a) accounts.push_back(a->clone());
    }
    Bank(Bank&&) noexcept = default;
    ~Bank() { stopAutoSave(); }

    void createSavings(const std::string& id, const std::string& owner, double bal = 0.0, double rate = 0.01);
    void createChecking(const std::string& id, const std::string& owner, double bal = 0.0, double overdraft = 200.0, double fee = 0.0);

    Account* findById(const std::string& id);

    bool transfer(const std::string& fromId, const std::string& toId, double amount);

    template<typename Func>
    void forEachAccount(Func f) const {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& u : accounts) if (u) f(*u);
    }

    std::vector<std::unique_ptr<Account>>& getAccounts() { return accounts; }

    void startAutoSave(std::function<void()> saver, unsigned intervalMs = 5000);
    void stopAutoSave();

private:
    std::vector<std::unique_ptr<Account>> accounts;
    mutable std::mutex mtx;

    std::atomic<bool> autosaveRunning{false};
    std::thread autosaveThread;
};

} // namespace MiniBank

#endif // BANK_H
