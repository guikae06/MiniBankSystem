#include "TransferDialog.h"
#include "ui_TransferDialog.h"
#include <QMessageBox>

TransferDialog::TransferDialog(MiniBank::Bank* b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferDialog),
    bank(b)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);
}

TransferDialog::~TransferDialog()
{
    delete ui;
}

void TransferDialog::on_transferButton_clicked()
{
    unsigned int fromId = ui->fromIdSpinBox->value();
    unsigned int toId = ui->toIdSpinBox->value();
    double amount = ui->amountDoubleSpinBox->value();

    auto fromAcc = bank->findAccount(fromId);
    auto toAcc = bank->findAccount(toId);

    if(!fromAcc || !toAcc) {
        QMessageBox::warning(this, "Error", "Invalid account(s)");
        return;
    }

    if(fromAcc->withdraw(amount)) {
        toAcc->deposit(amount);
        QMessageBox::information(this, "Success", "Transfer completed");
    } else {
        QMessageBox::warning(this, "Error", "Insufficient funds");
    }
}
