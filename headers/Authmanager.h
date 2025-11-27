#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>
#include "FileStorage.h"

class AuthManager {
public:
    explicit AuthManager(FileStorage *storage);
    bool signup(const QString &username, const QString &password, QString &err);
    bool login(const QString &username, const QString &password, int &userId, QString &err);

private:
    FileStorage *m_storage;
    QString generateSalt() const;
    QString hashPassword(const QString &password, const QString &salt) const;
    int nextUserId(const QJsonArray &users) const;
};

#endif // AUTHMANAGER_H
