#include <QApplication>
#include "LogInDialog.h"
#include "mainwindow.h"
#include "../headers/Bank.h"
#include "../headers/FileStorage.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MiniBank::Bank bank;
    MiniBank::FileStorage storage("accounts.txt");
    // load accounts (file may not exist on first run)
    try { storage.load(bank); } catch(...) {}

    // seed demo if empty
    if (bank.getAccounts().empty()) {
        bank.createSavings("SAV001", "Alice", 1000.0, 0.02);
        bank.createChecking("CHK001", "Bob", 500.0, 200.0, 1.0);
        storage.save(bank);
    }

    LogInDialog dlg(&storage);
    if (dlg.exec() != QDialog::Accepted) return 0;

    MainWindow w(&bank, &storage);
    w.show();

    int ret = a.exec();

    try { storage.save(bank); } catch(...) {}
    return ret;
}
