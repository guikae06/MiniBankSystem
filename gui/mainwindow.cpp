#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../headers/Bank.h"
#include "../headers/FileStorage.h"
#include "../headers/CheckingAccount.h"
#include "../headers/SavingsAccount.h"
#include <QMessageBox>
#include <QInputDialog>

using namespace MiniBank;

MainWindow::MainWindow(Bank* bankPtr, FileStorage* storagePtr, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), bank(bankPtr), storage(storagePtr)
{
    ui->setupUi(this);

    // simple black & gold theme
    this->setStyleSheet("QMainWindow{background:#121212;} QLabel{color:#D4AF37;} QPushButton{background:#D4AF37;color:#121212;} QLineEdit{background:#1F1F1F;color:#D4AF37;} QListWidget{background:#1B1B1B;color:#D4AF37;}");

    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::deposit);
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::withdraw);
    connect(ui->transferButton, &QPushButton::clicked, this, &MainWindow::transfer);
    connect(ui->interestButton, &QPushButton::clicked, this, &MainWindow::addInterest);
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::refresh);
    connect(ui->accountListWidget, &QListWidget::currentRowChanged, this, &MainWindow::refresh);

    refreshAccountView();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::refreshAccountView() {
    ui->accountListWidget->clear();
    if (!bank) return;
    auto &accounts = bank->getAccounts();
    for (size_t i=0;i<accounts.size();++i) {
        auto &a = accounts[i];
        if (!a) continue;
        QString label = QString::fromStdString(a->getAccountNumber()) + " - " + QString::fromStdString(a->getOwner())
                        + " : " + QString::number(a->getBalance(), 'f', 2);
        ui->accountListWidget->addItem(label);
    }
    int row = ui->accountListWidget->currentRow();
    if (row >= 0 && (size_t)row < bank->getAccounts().size()) {
        ui->balanceLabel->setText(QString::number(bank->getAccounts()[row]->getBalance(), 'f', 2));
    } else {
        ui->balanceLabel->setText("Select account");
    }
}

void MainWindow::deposit() {
    int idx = ui->accountListWidget->currentRow();
    if (idx < 0) { QMessageBox::warning(this, "Deposit", "Select account"); return; }
    bool ok = false;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) { QMessageBox::warning(this, "Deposit", "Enter amount"); return; }
    bank->getAccounts()[idx]->deposit(amount);
    if (storage) storage->save(*bank);
    refreshAccountView();
}

void MainWindow::withdraw() {
    int idx = ui->accountListWidget->currentRow();
    if (idx < 0) { QMessageBox::warning(this, "Withdraw", "Select account"); return; }
    bool ok = false;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) { QMessageBox::warning(this, "Withdraw", "Enter amount"); return; }
    Account* acc = bank->getAccounts()[idx].get();
    CheckingAccount* chk = dynamic_cast<CheckingAccount*>(acc);
    if (chk) {
        double allowed = chk->getBalance() + chk->getOverdraft();
        if (amount > allowed) { QMessageBox::warning(this, "Withdraw", "Insufficient funds"); return; }
    } else {
        if (amount > acc->getBalance()) { QMessageBox::warning(this, "Withdraw", "Insufficient funds"); return; }
    }
    acc->withdraw(amount);
    if (storage) storage->save(*bank);
    refreshAccountView();
}

void MainWindow::transfer() {
    int from = ui->accountListWidget->currentRow();
    if (from < 0) { QMessageBox::warning(this, "Transfer", "Select source account"); return; }
    QStringList targets;
    for (size_t i=0;i<bank->getAccounts().size();++i) {
        if ((int)i == from) continue;
        auto &a = bank->getAccounts()[i];
        targets << QString::fromStdString(a->getAccountNumber()) + " - " + QString::fromStdString(a->getOwner());
    }
    bool ok = false;
    QString chosen = QInputDialog::getItem(this, "Select target", "Target:", targets, 0, false, &ok);
    if (!ok || chosen.isEmpty()) return;
    int toIndex = -1;
    for (size_t i=0;i<bank->getAccounts().size();++i) {
        if ((int)i == from) continue;
        auto &a = bank->getAccounts()[i];
        QString label = QString::fromStdString(a->getAccountNumber()) + " - " + QString::fromStdString(a->getOwner());
        if (label == chosen) { toIndex = (int)i; break; }
    }
    if (toIndex < 0) return;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if (!ok || amount <= 0) { QMessageBox::warning(this, "Transfer", "Enter amount"); return; }
    if (!bank->transfer(bank->getAccounts()[from]->getAccountNumber(), bank->getAccounts()[toIndex]->getAccountNumber(), amount)) {
        QMessageBox::warning(this, "Transfer", "Failed (insufficient funds?)");
        return;
    }
    if (storage) storage->save(*bank);
    refreshAccountView();
}

void MainWindow::addInterest() {
    for (auto &u: bank->getAccounts()) {
        SavingsAccount* s = dynamic_cast<SavingsAccount*>(u.get());
        if (s) s->addInterest();
    }
    if (storage) storage->save(*bank);
    refreshAccountView();
}

void MainWindow::refresh() {
    refreshAccountView();
}
