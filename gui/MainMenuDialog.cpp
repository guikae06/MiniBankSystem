#include "MainMenuDialog.h"
#include "ui_MainMenuDialog.h"
#include "DepositWithdrawDialog.h"
#include "LoansDialog.h"
#include "InssuranceDialog.h"
#include "StockMarketDialog.h"
#include "TransferDialog.h"

MainMenuDialog::MainMenuDialog(MiniBank::Bank* b,
                               MiniBank::StockMarket* m,
                               MiniBank::Account* a,
                               QWidget *parent)
    : QDialog(parent),
    ui(new Ui::MainMenuDialog),
    bank(b),
    market(m),
    account(a)  // ✅ initialize logged-in account
{
    ui->setupUi(this);
    ui->labelBalance->setText(QString::number(account->getBalance(), 'f', 2));
}

MainMenuDialog::~MainMenuDialog()
{
    delete ui;
}

void MainMenuDialog::on_depositWithdrawButton_clicked()
{
    DepositWithdrawDialog dlg(account); // Pass logged-in account
    dlg.exec();
}

void MainMenuDialog::on_loansButton_clicked()
{
    LoansDialog dlg(account); // Pass logged-in account
    dlg.exec();
}

void MainMenuDialog::on_assuranceButton_clicked()
{
    InssuranceDialog dlg(account);
    dlg.exec();
}

void MainMenuDialog::on_stockMarketButton_clicked()
{
    StockMarketDialog dlg(account, market);
    dlg.exec();

    ui->labelBalance->setText(
        QString::number(account->getBalance(), 'f', 2)
        );
}

void MainMenuDialog::on_transferButton_clicked()
{
    TransferDialog dlg(account, bank); // sender = logged-in account
    dlg.exec();

    ui->labelBalance->setText(
        QString::number(account->getBalance(), 'f', 2)
        );
}
