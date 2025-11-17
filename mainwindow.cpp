#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include "SavingsAccount.h"
#include "CheckingAccount.h"

using namespace MiniBank;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    bank(std::make_unique<MiniBank::Bank>())   // now works, class is Bank
{
    ui->setupUi(this);

    // Create example accounts
    bank->createSavings("S123", "Alice", 1000.0, 0.02);
    bank->createChecking("C456", "Bob", 500.0, 200.0, 0.5);

    currentAccountId = "S123";
    currentAccount = bank->findById(currentAccountId);

    // connect UI elements to slots
    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::deposit);
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::withdraw);
    connect(ui->interestButton, &QPushButton::clicked, this, &MainWindow::addInterest);

    bank->startAutoSave("accounts.csv", 5000);

    refreshDisplay();
}

MainWindow::~MainWindow()
{
    bank->stopAutoSave();
    delete ui;
}

void MainWindow::deposit()
{
    bool ok = false;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if (!ok) { QMessageBox::warning(this, "Error", "Invalid amount"); return; }
    try {
        if (!currentAccount) throw std::runtime_error("No current account");
        currentAccount->deposit(amount);
        refreshDisplay();
    } catch (std::exception& ex) {
        QMessageBox::warning(this, "Error", ex.what());
    }
}

void MainWindow::withdraw()
{
    bool ok = false;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if (!ok) { QMessageBox::warning(this, "Error", "Invalid amount"); return; }
    try {
        if (!currentAccount) throw std::runtime_error("No current account");
        currentAccount->withdraw(amount);
        refreshDisplay();
    } catch (std::exception& ex) {
        QMessageBox::warning(this, "Error", ex.what());
    }
}

void MainWindow::addInterest()
{
    try {
        if (currentAccount && currentAccount->getAccountType() == 1) {
            SavingsAccount* sa = dynamic_cast<SavingsAccount*>(currentAccount);
            if (sa) sa->addInterest();
            refreshDisplay();
        } else {
            QMessageBox::information(this, "Info", "Current account is not a savings account");
        }
    } catch (std::exception& ex) {
        QMessageBox::warning(this, "Error", ex.what());
    }
}

void MainWindow::refreshDisplay()
{
    if (!currentAccount) {
        ui->balanceLabel->setText("No account");
        return;
    }
    QString text = QString::fromStdString(currentAccount->getAccountNumber())
                   + " / " + QString::fromStdString(currentAccount->getOwner())
                   + " : " + QString::number(currentAccount->getBalance());
    ui->balanceLabel->setText(text);
}
