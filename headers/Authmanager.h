#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <unordered_map>

namespace MiniBank {

class Authmanager {
public:
    Authmanager() = default;
    // store users in a simple file (username:password). Methods return true on success.
    bool signup(const std::string& username, const std::string& password, std::string& err);
    bool login(const std::string& username, const std::string& password, int& userId, std::string& err);

private:
    std::unordered_map<std::string, std::string> users;
    void loadFromFile();
    void saveToFile();
    std::string userFile{"users.txt"};
    int nextUserId{1};
};

} // namespace MiniBank

#endif // AUTHMANAGER_H
