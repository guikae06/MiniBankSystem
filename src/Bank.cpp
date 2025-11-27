#include "Bank.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

using namespace MiniBank;

bool Bank::transfer(const std::string &fromAcc, const std::string &toAcc, double amount, std::string &err, const QSqlDatabase &db) {
    std::lock_guard<std::mutex> lock(mtx);
    Account* aFrom = findById(fromAcc);
    Account* aTo = findById(toAcc);
    if(!aFrom || !aTo) { err = "Account not found"; return false; }
    // attempt withdraw
    if (CheckingAccount* chk = dynamic_cast<CheckingAccount*>(aFrom)) {
        if(!chk->withdraw(amount)) { err = "Insufficient funds"; return false; }
    } else {
        // SavingsAccount: ensure balance >= amount
        if (aFrom->getBalance() < amount) { err = "Insufficient funds"; return false; }
        // perform withdraw using deposit negative or implement withdraw in Savings
        // Here we directly reduce balance (since Account has protected balance, we do via a method ideally)
        aFrom->deposit(-amount); // using deposit(-amount) is a quick trick if withdraw isn't implemented
    }
    aTo->deposit(amount);

    // optionally persist transaction if db provided and open
    if (db.isValid() && db.isOpen()) {
        QSqlQuery q(db);
        if (!db.transaction()) {
            // continue but warn
        }
        q.prepare("INSERT INTO transactions(account_from, account_to, amount, type, note) VALUES(:f,:t,:a,:type,:note)");
        q.bindValue(":f", QString::fromStdString(fromAcc));
        q.bindValue(":t", QString::fromStdString(toAcc));
        q.bindValue(":a", amount);
        q.bindValue(":type", "transfer");
        q.bindValue(":note", "");
        if(!q.exec()) {
            // rollback and revert in memory changes
            db.rollback();
            // revert in-memory
            aFrom->deposit(amount);
            aTo->deposit(-amount);
            err = q.lastError().text().toStdString();
            return false;
        }
        db.commit();
    }
    return true;
}
