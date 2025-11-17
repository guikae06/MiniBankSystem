#ifndef BANK_H
#define BANK_H

#include <vector>
#include <memory>
#include <string>
#include <mutex>
#include <thread>
#include <atomic>
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

namespace MiniBank {

class Bank {
    std::vector<std::unique_ptr<Account>> accounts;
    std::mutex mtx;
    std::atomic<bool> autosaveRunning{false};
    std::thread autosaveThread;

public:
    Bank();
    ~Bank();

    void createSavings(const std::string& id, const std::string& owner, double bal = 0.0, double rate = 0.01);
    void createChecking(const std::string& id, const std::string& owner, double bal = 0.0,
                        double overdraft = 200.0, double fee = 0.0);
    Account* findById(const std::string& id);
    void saveToFile(const std::string& path);
    void startAutoSave(const std::string& path, unsigned intervalMs = 5000);
    void stopAutoSave();
    void demoNewDelete();
};

} // namespace MiniBank

#endif
