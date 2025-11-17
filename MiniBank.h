#ifndef MINIBANK_H
#define MINIBANK_H

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <mutex>
#include <thread>
#include <atomic>
#include <algorithm>
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

namespace MiniBank {

class MiniBank {
private:
    std::vector<std::unique_ptr<Account>> accounts;
    std::mutex mtx;
    std::atomic<bool> autosaveRunning{false};
    std::thread autosaveThread;

public:
    MiniBank() = default;
    ~MiniBank() { stopAutoSave(); }

    // create helpers
    void createSavings(const std::string& id, const std::string& owner, double bal = 0.0, double rate = 0.01);
    void createChecking(const std::string& id, const std::string& owner, double bal = 0.0, double overdraft = 200.0, double fee = 0.0);

    // find
    Account* findById(const std::string& id);

    // iterate with template
    template<typename Func>
    void forEach(Func f) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& u : accounts) if (u) f(*u);
    }

    // save/load
    void saveToFile(const std::string& path);
    void startAutoSave(const std::string& path, unsigned intervalMs = 5000);
    void stopAutoSave();

    // simple demo new/delete
    void demoNewDelete();
};

} // namespace MiniBank

#endif // MINIBANK_H
