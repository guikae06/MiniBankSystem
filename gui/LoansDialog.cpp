#include "LoansDialog.h"
#include "ui_LoansDialog.h"
#include <QMessageBox>

LoansDialog::LoansDialog(MiniBank::Account* acc, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LoansDialog),
    account(acc)
{
    ui->setupUi(this);

    // Back button closes dialog
    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);
}

LoansDialog::~LoansDialog()
{
    delete ui;
}

void LoansDialog::on_requestLoanButton_clicked()
{
    if (!account) {
        QMessageBox::warning(this, "Error", "No account available");
        return;
    }

    QMessageBox::information(
        this,
        "Not implemented",
        "Loan functionality is not implemented in Bank"
        );
}

void LoansDialog::on_payLoanButton_clicked()
{
    if (!account) {
        QMessageBox::warning(this, "Error", "No account available");
        return;
    }

    QMessageBox::information(
        this,
        "Not implemented",
        "Loan functionality is not implemented in Bank"
        );
}

void LoansDialog::on_backButton_clicked()
{
    accept(); // closes dialog
}
