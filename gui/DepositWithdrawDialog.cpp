#include "DepositWithdrawDialog.h"
#include "ui_DepositWithdrawDialog.h"
#include <QMessageBox>

DepositWithdrawDialog::DepositWithdrawDialog(MiniBank::Account* a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepositWithdrawDialog),
    account(a)
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
    double amount = ui->amountLineEdit->text().toDouble();
    account->deposit(amount);
    QMessageBox::information(this, "Success", "Deposit completed");
}

void DepositWithdrawDialog::on_withdrawBtn_clicked()
{
    double amount = ui->amountLineEdit->text().toDouble();
    if(account->withdraw(amount))
        QMessageBox::information(this, "Success", "Withdrawal completed");
    else
        QMessageBox::warning(this, "Error", "Insufficient funds");
}
