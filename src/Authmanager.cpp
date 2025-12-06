#include "../headers/Authmanager.h"
#include <fstream>
#include <sstream>

namespace MiniBank {

bool Authmanager::signup(const std::string& username, const std::string& password, std::string& err) {
    if (username.empty() || password.empty()) {
        err = "empty";
        return false;
    }
    loadFromFile();
    if (users.find(username) != users.end()) {
        err = "exists";
        return false;
    }
    users[username] = password;
    saveToFile();
    return true;
}

bool Authmanager::login(const std::string& username, const std::string& password, int& userId, std::string& err) {
    loadFromFile();
    auto it = users.find(username);
    if (it == users.end() || it->second != password) {
        err = "invalid";
        return false;
    }
    // simple userId mapping: hash of username for demo
    userId = static_cast<int>(std::hash<std::string>{}(username) & 0x7fffffff);
    return true;
}

void Authmanager::loadFromFile() {
    if (users.size()) return; // already loaded
    std::ifstream ifs(userFile);
    if (!ifs) return;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        auto p = line.find(':');
        if (p == std::string::npos) continue;
        std::string user = line.substr(0, p);
        std::string pass = line.substr(p+1);
        users[user] = pass;
    }
}

void Authmanager::saveToFile() {
    std::ofstream ofs(userFile, std::ios::trunc);
    if (!ofs) return;
    for (const auto& kv : users) {
        ofs << kv.first << ':' << kv.second << '\n';
    }
}

} // namespace MiniBank
