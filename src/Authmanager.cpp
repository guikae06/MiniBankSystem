#include "headers/Authmanager.h"
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QJsonArray>
#include <QJsonObject>

AuthManager::AuthManager(FileStorage *storage) : m_storage(storage) {}

QString AuthManager::generateSalt() const {
    QByteArray b;
    for (int i = 0; i < 16; ++i) b.append((char)QRandomGenerator::global()->bounded(33, 127));
    return QString::fromLatin1(b.toBase64());
}

QString AuthManager::hashPassword(const QString &password, const QString &salt) const {
    QByteArray combined = password.toUtf8() + salt.toUtf8();
    QByteArray hash = QCryptographicHash::hash(combined, QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

int AuthManager::nextUserId(const QJsonArray &users) const {
    int maxId = 0;
    for (const QJsonValue &v : users) {
        if (!v.isObject()) continue;
        QJsonObject o = v.toObject();
        if (o.contains("id")) maxId = std::max(maxId, o["id"].toInt());
    }
    return maxId + 1;
}

bool AuthManager::signup(const QString &username, const QString &password, QString &err) {
    if (!m_storage) { err = "No storage"; return false; }
    if (username.trimmed().isEmpty()) { err = "Username empty"; return false; }
    if (password.isEmpty()) { err = "Password empty"; return false; }

    if (!m_storage->ensureLoaded(err)) return false;

    QJsonObject root = m_storage->root();
    QJsonArray users = root.value("users").toArray();

    // check exists
    for (const QJsonValue &v : users) {
        if (!v.isObject()) continue;
        if (v.toObject().value("username").toString() == username) {
            err = "User exists";
            return false;
        }
    }

    QString salt = generateSalt();
    QString hashed = hashPassword(password, salt);
    int newId = nextUserId(users);

    QJsonObject newUser;
    newUser.insert("id", newId);
    newUser.insert("username", username);
    newUser.insert("password_hash", hashed);
    newUser.insert("salt", salt);
    newUser.insert("created_at", QDateTime::currentDateTimeUtc().toString(Qt::ISODate));

    users.append(newUser);
    root.insert("users", users);
    m_storage->setRoot(root);
    return m_storage->save(err);
}

bool AuthManager::login(const QString &username, const QString &password, int &userId, QString &err) {
    if (!m_storage) { err = "No storage"; return false; }
    if (!m_storage->ensureLoaded(err)) return false;

    QJsonObject root = m_storage->root();
    QJsonArray users = root.value("users").toArray();

    for (const QJsonValue &v : users) {
        if (!v.isObject()) continue;
        QJsonObject o = v.toObject();
        if (o.value("username").toString() == username) {
            QString storedHash = o.value("password_hash").toString();
            QString salt = o.value("salt").toString();
            QString hashed = hashPassword(password, salt);
            if (hashed == storedHash) {
                userId = o.value("id").toInt();
                return true;
            } else {
                err = "Bad credentials";
                return false;
            }
        }
    }
    err = "User not found";
    return false;
}
