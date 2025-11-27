#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../libs/json.hpp"

using json = nlohmann::json;

class FileDB {
public:
    FileDB(const std::string& basePath);

    // Load all JSON files
    bool load();

    // Save all JSON files
    bool save();

    // --- USERS ---
    bool userExists(const std::string& username);
    bool createUser(const std::string& username, const std::string& password);
    bool validateUser(const std::string& username, const std::string& password);

    // --- ACCOUNTS ---
    double getBalance(const std::string& username);
    bool updateBalance(const std::string& username, double newBalance);

    // --- STOCKS ---
    json getStocks();
    void updateStock(const std::string& symbol, double newPrice);

private:
    std::string basePath;

    json usersJSON;
    json accountsJSON;
    json stocksJSON;

    bool loadFile(const std::string& file, json& j);
    bool saveFile(const std::string& file, const json& j);
};
