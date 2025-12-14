#include "MainMenuDialog.h"
#include "ui_MainMenuDialog.h"
#include "DepositWithdrawDialog.h"
#include "LoansDialog.h"
#include "AssuranceDialog.h"
#include "StockMarketDialog.h"
#include "TransferDialog.h"

MainMenuDialog::MainMenuDialog(MiniBank::Bank* b,
                               MiniBank::StockMarket* m,
                               QWidget *parent)
    : QDialog(parent),
    ui(new Ui::MainMenuDialog),
    bank(b),
    market(m)
{
    ui->setupUi(this);
}

MainMenuDialog::~MainMenuDialog()
{
    delete ui;
}

void MainMenuDialog::on_depositWithdrawButton_clicked()
{
    DepositWithdrawDialog dlg(bank);
    dlg.exec();
}

void MainMenuDialog::on_loansButton_clicked()
{
    LoansDialog dlg(bank);
    dlg.exec();
}

void MainMenuDialog::on_assuranceButton_clicked()
{
    AssuranceDialog dlg(bank);
    dlg.exec();
}

void MainMenuDialog::on_stockMarketButton_clicked()
{
    StockMarketDialog dlg(bank, market);
    dlg.exec();
}

void MainMenuDialog::on_transferButton_clicked()
{
    TransferDialog dlg(bank);
    dlg.exec();
}
