#include "AssuranceDialog.h"
#include "ui_AssuranceDialog.h"
#include <QMessageBox>

AssuranceDialog::AssuranceDialog(MiniBank::Bank* b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssuranceDialog),
    bank(b)
{
    ui->setupUi(this);
    setWindowTitle("Insurance");
}

AssuranceDialog::~AssuranceDialog()
{
    delete ui;
}

void AssuranceDialog::showMessage(const QString& msg) {
    QMessageBox::information(this, "Info", msg);
}

void AssuranceDialog::on_buyButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    double amount = ui->amountDoubleSpinBox->value();

    MiniBank::Account* acc = bank->findAccount(accId);
    if(!acc) {
        showMessage("Invalid account ID.");
        return;
    }

    if(acc->withdraw(amount)) {
        showMessage(QString("Insurance purchased for account %1: %2").arg(accId).arg(amount));
    } else {
        showMessage("Insufficient funds to buy insurance.");
    }
}
