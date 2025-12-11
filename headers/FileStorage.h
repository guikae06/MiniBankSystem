#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "Bank.h"
#include <string>
#include <fstream>
#include <exception>

namespace MiniBank {

class FileStorage {
private:
    std::string filename;

public:
    FileStorage(const std::string& file);
    void save(const Bank& bank);
    void load(Bank& bank);
};

}

#endif // FILESTORAGE_H
