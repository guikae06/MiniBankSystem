#include "LoansDialog.h"
#include "ui_LoansDialog.h"
#include <QMessageBox>

LoansDialog::LoansDialog(MiniBank::Bank* b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoansDialog),
    bank(b)
{
    ui->setupUi(this);
    setWindowTitle("Loans");
}

LoansDialog::~LoansDialog()
{
    delete ui;
}

void LoansDialog::showMessage(const QString& msg) {
    QMessageBox::information(this, "Info", msg);
}

void LoansDialog::on_requestLoanButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    double amount = ui->amountDoubleSpinBox->value();

    MiniBank::Account* acc = bank->findAccount(accId);
    if(!acc) {
        showMessage("Invalid account ID.");
        return;
    }

    acc->deposit(amount); // loan adds money
    showMessage(QString("Loan of %1 granted to account %2").arg(amount).arg(accId));
}

void LoansDialog::on_payLoanButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    double amount = ui->amountDoubleSpinBox->value();

    MiniBank::Account* acc = bank->findAccount(accId);
    if(!acc) {
        showMessage("Invalid account ID.");
        return;
    }

    if(acc->withdraw(amount)) {
        showMessage(QString("Loan payment of %1 successful for account %2").arg(amount).arg(accId));
    } else {
        showMessage("Insufficient funds to pay loan.");
    }
}
