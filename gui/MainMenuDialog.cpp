#include "MainMenuDialog.h"
#include "ui_MainMenuDialog.h"
#include "DepositWithdrawDialog.h"
#include "LoansDialog.h"
#include "InssuranceDialog.h"
#include "StockMarketDialog.h"

MainMenuDialog::MainMenuDialog(MiniBank::Bank* b,
                               MiniBank::StockMarket* m,
                               MiniBank::Account* a,
                               QWidget *parent)
    : QDialog(parent),
    ui(new Ui::MainMenuDialog),
    bank(b),
    market(m),
    account(a)
{
    ui->setupUi(this);
    refreshAccountInfo();
}

MainMenuDialog::~MainMenuDialog()
{
    delete ui;
}

void MainMenuDialog::refreshAccountInfo()
{
    // Account label: ACC1 (guikae)
    ui->labelAccount->setText(
        QString::fromStdString(account->getAccountNumber()) +
        " (" +
        QString::fromStdString(account->getOwnerName()) +
        ")"
        );

    // Balance label: Balance: €0.00
    ui->labelBalance->setText(
        "Balance: €" + QString::number(account->getBalance(), 'f', 2)
        );
}

void MainMenuDialog::on_depositWithdrawButton_clicked()
{
    DepositWithdrawDialog dlg(account, this);
    dlg.exec();
    refreshAccountInfo(); // 🔥 update immediately
}

void MainMenuDialog::on_loansButton_clicked()
{
    LoansDialog dlg(account, this);
    dlg.exec();
    refreshAccountInfo();
}

void MainMenuDialog::on_inssuranceButton_clicked()
{
    InssuranceDialog dlg(account, this);
    dlg.exec();
    refreshAccountInfo();
}

void MainMenuDialog::on_stockMarketButton_clicked()
{
    StockMarketDialog dlg(account, market, this);
    dlg.exec();
    refreshAccountInfo();
}
