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

    // For demonstration, we just have a single account. If multiple, fill allAccounts
    allAccounts.push_back(account);
    refreshAccounts();
}

DepositWithdrawDialog::~DepositWithdrawDialog()
{
    delete ui;
}

void DepositWithdrawDialog::refreshAccounts()
{
    ui->accountList->clear();
    for (auto acc : allAccounts) {
        ui->accountList->addItem(QString::fromStdString(acc->getAccountNumber()) +
                                 " (" + QString::fromStdString(acc->getOwnerName()) + ")" +
                                 " - €" + QString::number(acc->getBalance()));
    }
    ui->accountList->setCurrentRow(0);
    refreshHistory();
}

void DepositWithdrawDialog::refreshHistory()
{
    ui->historyListWidget->clear(); // <-- fixed widget name
    int row = ui->accountList->currentRow();
    if (row < 0 || row >= allAccounts.size()) return;

    auto acc = allAccounts[row];
    for (const auto& tx : acc->getHistory()) {
        ui->historyListWidget->addItem(
            QString::fromStdString(tx.type) + " €" + QString::number(tx.amount)
            );
    }
}

void DepositWithdrawDialog::on_accountList_currentRowChanged(int row)
{
    Q_UNUSED(row);
    refreshHistory();
}

void DepositWithdrawDialog::on_depositBtn_clicked()
{
    double amount = ui->amountLineEdit->text().toDouble();
    if (amount <= 0) return;

    int row = ui->accountList->currentRow();
    if (row < 0 || row >= allAccounts.size()) return;

    allAccounts[row]->deposit(amount);
    QMessageBox::information(this, "Success", "Deposit completed");
    refreshAccounts();
}

void DepositWithdrawDialog::on_withdrawBtn_clicked()
{
    double amount = ui->amountLineEdit->text().toDouble();
    if (amount <= 0) return;

    int row = ui->accountList->currentRow();
    if (row < 0 || row >= allAccounts.size()) return;

    if (allAccounts[row]->withdraw(amount))
        QMessageBox::information(this, "Success", "Withdrawal completed");
    else
        QMessageBox::warning(this, "Error", "Insufficient funds");

    refreshAccounts();
}
