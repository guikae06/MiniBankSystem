#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MiniBank::Bank* bank,
                       MiniBank::FileStorage* storage,
                       MiniBank::StockMarket* market,
                       QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    bank_(bank),
    storage_(storage),
    market_(market)
{
    ui->setupUi(this);
    refreshAccountList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_depositBtn_clicked()
{
    QString accNum = ui->accountNumberLineEdit->text();
    double amount = ui->amountLineEdit->text().toDouble();

    auto acc = bank_->findByNumber(accNum.toStdString());
    if (!acc) {
        QMessageBox::warning(this, "Error", "Account not found!");
        return;
    }

    acc->deposit(amount);
    storage_->save(*bank_);
    refreshAccountList();
}

void MainWindow::on_withdrawBtn_clicked()
{
    QString accNum = ui->accountNumberLineEdit->text();
    double amount = ui->amountLineEdit->text().toDouble();

    auto acc = bank_->findByNumber(accNum.toStdString());
    if (!acc) {
        QMessageBox::warning(this, "Error", "Account not found!");
        return;
    }

    acc->withdraw(amount);
    storage_->save(*bank_);
    refreshAccountList();
}

void MainWindow::refreshAccountList()
{
    ui->accountsListWidget->clear();

    auto accounts = bank_->snapshot();
    for (auto& acc : accounts) {
        QString text = QString::fromStdString(acc->getAccountNumber()) +
                       " - Balance: " +
                       QString::number(acc->getBalance(), 'f', 2);
        ui->accountsListWidget->addItem(text);
    }
}
