#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "Account.h"


#include <QMessageBox>

using namespace MiniBank;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Voorbeeldaccounts
    sa = new SavingsAccount("S123", 1000, 0.05);
    ca = new CheckingAccount("C456", 500, 200);

    // Verbind knoppen met slots
    connect(ui->depositButton, &QPushButton::clicked, this, &MainWindow::deposit);
    connect(ui->withdrawButton, &QPushButton::clicked, this, &MainWindow::withdraw);
    connect(ui->interestButton, &QPushButton::clicked, this, &MainWindow::addInterest);
}

MainWindow::~MainWindow()
{
    delete sa;
    delete ca;
    delete ui;
}

void MainWindow::deposit()
{
    bool ok;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if(!ok) return;

    sa->deposit(amount);
    ca->deposit(amount);

    ui->balanceLabel->setText("Savings saldo: " + QString::number(sa->getBalance()) +
                              " | Checking saldo: " + QString::number(ca->getBalance()));
}

void MainWindow::withdraw()
{
    bool ok;
    double amount = ui->amountEdit->text().toDouble(&ok);
    if(!ok) return;

    sa->withdraw(amount);
    ca->withdraw(amount);

    ui->balanceLabel->setText("Savings saldo: " + QString::number(sa->getBalance()) +
                              " | Checking saldo: " + QString::number(ca->getBalance()));
}

void MainWindow::addInterest() {
    sa->addInterest();
    ui->balanceLabel->setText("Savings saldo: " + QString::number(sa->getBalance()));
}
