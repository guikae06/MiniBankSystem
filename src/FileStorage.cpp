#include "FileStorage.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace MiniBank {

void FileStorage::save(const Bank& bank) {
    std::ofstream ofs(path, std::ios::trunc);
    if (!ofs) throw std::runtime_error("Cannot open file for save: " + path);

    bank.forEachAccount([&ofs](const Account& a) {
        ofs << static_cast<int>(a.getAccountType()) << ','
            << a.getAccountNumber() << ',' << a.getOwner() << ','
            << a.getBalance();
        if (a.getAccountType() == AccountType::Checking) {
            const CheckingAccount& c = static_cast<const CheckingAccount&>(a);
            ofs << ',' << c.getOverdraft() << ',' << c.getFee();
        } else if (a.getAccountType() == AccountType::Savings) {
            const SavingsAccount& s = static_cast<const SavingsAccount&>(a);
            ofs << ',' << s.getInterestRate();
        }
        ofs << '\n';
    });
}

void FileStorage::load(Bank& bank) {
    std::ifstream ifs(path);
    if (!ifs) return;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string piece;
        std::vector<std::string> parts;
        while (std::getline(ss, piece, ',')) parts.push_back(piece);
        if (parts.size() < 4) continue;
        int type = std::stoi(parts[0]);
        std::string id = parts[1];
        std::string owner = parts[2];
        double bal = std::stod(parts[3]);
        if (type == static_cast<int>(AccountType::Checking) && parts.size() >= 6) {
            double overd = std::stod(parts[4]);
            double fee = std::stod(parts[5]);
            bank.createChecking(id, owner, bal, overd, fee);
        } else if (type == static_cast<int>(AccountType::Savings) && parts.size() >= 5) {
            double rate = std::stod(parts[4]);
            bank.createSavings(id, owner, bal, rate);
        }
    }
}

} // namespace MiniBank
