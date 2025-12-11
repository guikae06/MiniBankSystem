#include "FileStorage.h"
#include <iostream>

namespace MiniBank {

FileStorage::FileStorage(const std::string& file) : filename(file) {}

void FileStorage::save(const Bank& bank) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) throw std::runtime_error("Cannot open file for saving");

    auto accounts = bank.getAccounts();
    size_t size = accounts.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (auto acc : accounts) {
        unsigned int id = acc->getId();
        ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));

        double balance = acc->getBalance();
        ofs.write(reinterpret_cast<const char*>(&balance), sizeof(balance));

        size_t len = acc->getOwnerName().size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(acc->getOwnerName().c_str(), len);

        bool isSavings = dynamic_cast<SavingsAccount*>(acc) != nullptr;
        ofs.write(reinterpret_cast<const char*>(&isSavings), sizeof(isSavings));
    }
}

void FileStorage::load(Bank& bank) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) throw std::runtime_error("Cannot open file for loading");

    size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));

    for (size_t i = 0; i < size; ++i) {
        unsigned int id;
        double balance;
        size_t len;

        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
        ifs.read(reinterpret_cast<char*>(&balance), sizeof(balance));
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));

        std::string owner(len, '\0');
        ifs.read(&owner[0], len);

        bool isSavings;
        ifs.read(reinterpret_cast<char*>(&isSavings), sizeof(isSavings));

        if (isSavings)
            bank.createSavingsAccount(owner, balance);
        else
            bank.createCheckingAccount(owner, balance);
    }
}

} // namespace MiniBank
