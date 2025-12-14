#include "LoansDialog.h"
#include "ui_LoansDialog.h"
#include <QMessageBox>

LoansDialog::LoansDialog(MiniBank::Account* acc, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LoansDialog),
    account(acc)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);

    refreshLoans();
}

LoansDialog::~LoansDialog()
{
    delete ui;
}

void LoansDialog::refreshLoans()
{
    ui->loansListWidget->clear();

    if (!account) return;

    auto loans = account->getLoans();
    for (size_t i = 0; i < loans.size(); ++i) {
        const auto& loan = loans[i];
        ui->loansListWidget->addItem(
            QString("Loan %1: €%2 (%3%)")
                .arg(i+1)
                .arg(loan.amount)
                .arg(loan.interestRate)
            );
    }
}

void LoansDialog::on_requestLoanButton_clicked()
{
    if (!account) return;

    double amount = ui->amountSpinBox->value();
    double interest = ui->interestSpinBox->value();

    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Amount must be positive");
        return;
    }

    account->requestLoan(amount, interest);
    QMessageBox::information(this, "Success", "Loan granted");
    refreshLoans();
}

void LoansDialog::on_payLoanButton_clicked()
{
    if (!account) return;

    int row = ui->loansListWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Select a loan first");
        return;
    }

    if (account->payLoan(row)) {
        QMessageBox::information(this, "Success", "Loan paid");
        refreshLoans();
    } else {
        QMessageBox::warning(this, "Error", "Insufficient balance");
    }
}

void LoansDialog::on_backButton_clicked()
{
    accept(); // close dialog
}
