#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <map>

class AuthManager {
private:
    std::map<std::string, std::string> users; // username -> hashed password

    std::string hashPassword(const std::string& password) const;

public:
    AuthManager();
    bool signup(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
};

#endif // AUTHMANAGER_H
