#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <string>
#include "Bank.h"

namespace MiniBank {

class FileStorage {
public:
    explicit FileStorage(const std::string& filepath) : path(filepath) {}
    void save(const Bank& bank);
    void load(Bank& bank);
private:
    std::string path;
};

} // namespace MiniBank

#endif // FILESTORAGE_H
