#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "SavingsAccount.h"
#include "CheckingAccount.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bank(std::make_unique<Bank>())
{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: #1e1e1e; }"
                        "QPushButton { background-color: gold; color: black; border-radius: 5px; padding: 5px; }"
                        "QLabel { color: gold; }"
                        "QLineEdit { background-color: #333333; color: gold; border: 1px solid gold; }");

    bank->createSavings("SAV001", "Alice", 1000.0, 0.02);
    bank->createChecking("CHK001", "Bob", 500.0, 200.0, 1.0);

    defaultAccount = bank->findById("SAV001");

    if(defaultAccount)
        ui->balanceLabel->setText("Balance: " + QString::number(defaultAccount->getBalance()));

    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::deposit);
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::withdraw);
    connect(ui->interestButton, &QPushButton::clicked, this, &MainWindow::addInterest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deposit()
{
    if(!defaultAccount) return;

    double amount = ui->amountLineEdit->text().toDouble();
    defaultAccount->deposit(amount);
    ui->balanceLabel->setText("Balance: " + QString::number(defaultAccount->getBalance()));
}

void MainWindow::withdraw()
{
    if(!defaultAccount) return;

    double amount = ui->amountLineEdit->text().toDouble();

    if(CheckingAccount* chk = dynamic_cast<CheckingAccount*>(defaultAccount)) {
        if(amount > chk->getBalance() + chk->getOverdraft()) {
            QMessageBox::warning(this, "Withdraw Failed", "Insufficient funds!");
            return;
        }
    } else if(SavingsAccount* sav = dynamic_cast<SavingsAccount*>(defaultAccount)) {
        if(amount > sav->getBalance()) {
            QMessageBox::warning(this, "Withdraw Failed", "Insufficient funds!");
            return;
        }
    }

    defaultAccount->withdraw(amount);
    ui->balanceLabel->setText("Balance: " + QString::number(defaultAccount->getBalance()));
}

void MainWindow::addInterest()
{
    if(!defaultAccount) return;

    if(SavingsAccount* sav = dynamic_cast<SavingsAccount*>(defaultAccount)) {
        sav->addInterest();
        ui->balanceLabel->setText("Balance: " + QString::number(defaultAccount->getBalance()));
    } else {
        QMessageBox::information(this, "Interest", "Interest only applies to savings accounts.");
    }
}
