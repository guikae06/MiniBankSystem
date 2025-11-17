#include "Bank.h"
#include <fstream>
#include <algorithm>
#include <chrono>

namespace MiniBank {

Bank::Bank() = default;

Bank::~Bank() {
    stopAutoSave();
}

void Bank::createSavings(const std::string& id, const std::string& owner, double bal, double rate) {
    std::unique_ptr<Account> p = std::make_unique<SavingsAccount>(id, owner, bal, rate);
    std::lock_guard<std::mutex> lock(mtx);
    accounts.push_back(std::move(p));
}

void Bank::createChecking(const std::string& id, const std::string& owner, double bal, double overdraft, double fee) {
    std::unique_ptr<Account> p = std::make_unique<CheckingAccount>(id, owner, bal, overdraft, fee);
    std::lock_guard<std::mutex> lock(mtx);
    accounts.push_back(std::move(p));
}

Account* Bank::findById(const std::string& id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::find_if(accounts.begin(), accounts.end(), [&](const std::unique_ptr<Account>& a) {
        return a && a->getAccountNumber() == id;
    });
    return (it != accounts.end()) ? it->get() : nullptr;
}

void Bank::saveToFile(const std::string& path) {
    std::lock_guard<std::mutex> lock(mtx);
    std::ofstream ofs(path, std::ios::trunc);
    if (!ofs) throw std::runtime_error("Cannot open file for save");
    for (const auto& a : accounts) {
        if (!a) continue;
        ofs << a->getAccountNumber() << ',' << a->getOwner() << ',' << a->getBalance() << ',' << int(a->getAccountType()) << '\n';
    }
}

void Bank::startAutoSave(const std::string& path, unsigned intervalMs) {
    if (autosaveRunning.load()) return;
    autosaveRunning = true;
    autosaveThread = std::thread([this, path, intervalMs]() {
        while (autosaveRunning.load()) {
            try { this->saveToFile(path); } catch (...) {}
            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        }
    });
}

void Bank::stopAutoSave() {
    if (!autosaveRunning.load()) return;
    autosaveRunning = false;
    if (autosaveThread.joinable()) autosaveThread.join();
}

void Bank::demoNewDelete() {
    Account* a = new CheckingAccount("tmp", "tmp owner", 10.0, 100.0, 1.0);
    delete a;
}

} // namespace MiniBank
