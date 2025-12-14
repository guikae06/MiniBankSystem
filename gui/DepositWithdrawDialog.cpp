#include "DepositWithdrawDialog.h"
#include "ui_DepositWithdrawDialog.h"
#include <QMessageBox>

DepositWithdrawDialog::DepositWithdrawDialog(MiniBank::Bank* b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepositWithdrawDialog),
    bank(b)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);
}

DepositWithdrawDialog::~DepositWithdrawDialog()
{
    delete ui;
}

void DepositWithdrawDialog::on_depositBtn_clicked()
{
    unsigned int accId = ui->accountNumberLineEdit->text().toUInt();
    double amount = ui->amountLineEdit->text().toDouble();
    auto acc = bank->findAccount(accId);
    if(!acc) {
        QMessageBox::warning(this, "Error", "Account not found");
        return;
    }
    acc->deposit(amount);
    QMessageBox::information(this, "Success", "Deposit completed");
}

void DepositWithdrawDialog::on_withdrawBtn_clicked()
{
    unsigned int accId = ui->accountNumberLineEdit->text().toUInt();
    double amount = ui->amountLineEdit->text().toDouble();
    auto acc = bank->findAccount(accId);
    if(!acc) {
        QMessageBox::warning(this, "Error", "Account not found");
        return;
    }
    if(acc->withdraw(amount))
        QMessageBox::information(this, "Success", "Withdrawal completed");
    else
        QMessageBox::warning(this, "Error", "Insufficient funds");
}
