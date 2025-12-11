#include "AuthManager.h"
#include <functional>

AuthManager::AuthManager() {}

std::string AuthManager::hashPassword(const std::string& password) const {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

bool AuthManager::signup(const std::string& username, const std::string& password) {
    if (users.find(username) != users.end()) return false;
    users[username] = hashPassword(password);
    return true;
}

bool AuthManager::login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it == users.end()) return false;
    return it->second == hashPassword(password);
}
