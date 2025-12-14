#include "LoansDialog.h"
#include "ui_LoansDialog.h"
#include <QMessageBox>

LoansDialog::LoansDialog(MiniBank::Bank* b, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LoansDialog),
    bank(b)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);
}

LoansDialog::~LoansDialog()
{
    delete ui;
}

void LoansDialog::on_requestLoanButton_clicked()
{
    QMessageBox::information(
        this,
        "Not implemented",
        "Loan functionality is not implemented in Bank"
        );
}

void LoansDialog::on_payLoanButton_clicked()
{
    QMessageBox::information(
        this,
        "Not implemented",
        "Loan functionality is not implemented in Bank"
        );
}
