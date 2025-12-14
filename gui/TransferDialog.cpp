#include "TransferDialog.h"
#include "ui_TransferDialog.h"
#include <QMessageBox>

TransferDialog::TransferDialog(MiniBank::Account* senderAccount, MiniBank::Bank* b, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::TransferDialog),
    sender(senderAccount),
    bank(b)
{
    ui->setupUi(this);

    // Back button closes the dialog
    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);
}

TransferDialog::~TransferDialog()
{
    delete ui;
}

void TransferDialog::on_transferButton_clicked()
{
    if (!sender || !bank) {
        QMessageBox::warning(this, "Error", "Sender account or bank not available");
        return;
    }

    unsigned int toId = ui->toIdSpinBox->value();
    double amount = ui->amountDoubleSpinBox->value();

    auto toAcc = bank->findAccount(toId);
    if(!toAcc) {
        QMessageBox::warning(this, "Error", "Target account not found");
        return;
    }

    if(sender->withdraw(amount)) {
        toAcc->deposit(amount);
        QMessageBox::information(this, "Success", "Transfer completed");
    } else {
        QMessageBox::warning(this, "Error", "Insufficient funds");
    }
}

void TransferDialog::on_backButton_clicked()
{
    accept(); // closes dialog
}
