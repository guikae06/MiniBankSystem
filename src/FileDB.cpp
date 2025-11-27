#include "FileDB.h"
#include <fstream>

FileDB::FileDB(const std::string& basePath) : basePath(basePath) {}

// ---------------- LOAD & SAVE ----------------------

bool FileDB::load() {
    return loadFile("users.json", usersJSON) &&
           loadFile("accounts.json", accountsJSON) &&
           loadFile("stocks.json", stocksJSON);
}

bool FileDB::save() {
    return saveFile("users.json", usersJSON) &&
           saveFile("accounts.json", accountsJSON) &&
           saveFile("stocks.json", stocksJSON);
}

bool FileDB::loadFile(const std::string& file, json& j) {
    std::ifstream f(basePath + "/" + file);
    if (!f.is_open()) return false;

    f >> j;
    return true;
}

bool FileDB::saveFile(const std::string& file, const json& j) {
    std::ofstream f(basePath + "/" + file);
    if (!f.is_open()) return false;

    f << j.dump(4);
    return true;
}

// ---------------- USERS ----------------------

bool FileDB::userExists(const std::string& username) {
    return usersJSON.contains(username);
}

bool FileDB::createUser(const std::string& username, const std::string& password) {
    if (userExists(username)) return false;

    usersJSON[username]["password"] = password;
    accountsJSON[username]["balance"] = 0.0;

    return save();
}

bool FileDB::validateUser(const std::string& username, const std::string& password) {
    if (!userExists(username)) return false;
    return usersJSON[username]["password"] == password;
}

// ---------------- ACCOUNTS ----------------------

double FileDB::getBalance(const std::string& username) {
    if (!accountsJSON.contains(username)) return 0.0;
    return accountsJSON[username]["balance"];
}

bool FileDB::updateBalance(const std::string& username, double newBalance) {
    accountsJSON[username]["balance"] = newBalance;
    return save();
}

// ---------------- STOCKS ----------------------

json FileDB::getStocks() {
    return stocksJSON;
}

void FileDB::updateStock(const std::string& symbol, double newPrice) {
    stocksJSON[symbol] = newPrice;
    save();
}
