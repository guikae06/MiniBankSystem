#include "../headers/Bank.h"
#include "../headers/CheckingAccount.h"
#include "../headers/SavingsAccount.h"
#include <algorithm>
#include <chrono>
#include <thread>

namespace MiniBank {

void Bank::createSavings(const std::string& id, const std::string& owner, double bal, double rate) {
    std::lock_guard<std::mutex> lock(mtx);
    accounts.push_back(std::make_unique<SavingsAccount>(id, owner, bal, rate));
}

void Bank::createChecking(const std::string& id, const std::string& owner, double bal, double overdraft, double fee) {
    std::lock_guard<std::mutex> lock(mtx);
    accounts.push_back(std::make_unique<CheckingAccount>(id, owner, bal, overdraft, fee));
}

Account* Bank::findById(const std::string& id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::find_if(accounts.begin(), accounts.end(), [&](const std::unique_ptr<Account>& a) {
        return a && a->getAccountNumber() == id;
    });
    return it != accounts.end() ? it->get() : nullptr;
}

bool Bank::transfer(const std::string& fromId, const std::string& toId, double amount) {
    if (amount <= 0) return false;
    std::lock_guard<std::mutex> lock(mtx);
    Account* a = nullptr;
    Account* b = nullptr;
    for (auto& u : accounts) {
        if (!u) continue;
        if (u->getAccountNumber() == fromId) a = u.get();
        if (u->getAccountNumber() == toId) b = u.get();
    }
    if (!a || !b) return false;
    if (!a->withdraw(amount)) return false;
    b->deposit(amount);
    return true;
}

void Bank::startAutoSave(std::function<void()> saver, unsigned intervalMs) {
    if (autosaveRunning.load()) return;
    autosaveRunning = true;
    autosaveThread = std::thread([this, saver, intervalMs]() {
        while (autosaveRunning.load()) {
            try { saver(); } catch (...) {}
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        }
    });
}

void Bank::stopAutoSave() {
    if (!autosaveRunning.load()) return;
    autosaveRunning = false;
    if (autosaveThread.joinable()) autosaveThread.join();
}

} // namespace MiniBank
