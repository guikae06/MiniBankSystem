#include "TransferDialog.h"
#include "ui_TransferDialog.h"
#include <QMessageBox>

TransferDialog::TransferDialog(MiniBank::Bank* b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferDialog),
    bank(b)
{
    ui->setupUi(this);
    setWindowTitle("Transfer Funds");
}

TransferDialog::~TransferDialog()
{
    delete ui;
}

void TransferDialog::showMessage(const QString& msg) {
    QMessageBox::information(this, "Info", msg);
}

void TransferDialog::on_transferButton_clicked()
{
    unsigned int fromId = ui->fromIdSpinBox->value();
    unsigned int toId = ui->toIdSpinBox->value();
    double amount = ui->amountDoubleSpinBox->value();

    MiniBank::Account* from = bank->findAccount(fromId);
    MiniBank::Account* to = bank->findAccount(toId);

    if(!from || !to) {
        showMessage("Invalid account ID(s).");
        return;
    }

    if(bank->transfer(from, to, amount)) {
        showMessage("Transfer successful!");
    } else {
        showMessage("Transfer failed: insufficient funds.");
    }
}
