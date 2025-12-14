#include "StockMarketDialog.h"
#include "ui_StockMarketDialog.h"
#include <QMessageBox>

StockMarketDialog::StockMarketDialog(MiniBank::Bank* b,
                                     MiniBank::StockMarket* m,
                                     QWidget *parent)
    : QDialog(parent),
    ui(new Ui::StockMarketDialog),
    bank(b),
    market(m)
{
    ui->setupUi(this);
    ui->stockTextEdit->setText("Market ready");
}

StockMarketDialog::~StockMarketDialog()
{
    delete ui;
}

void StockMarketDialog::on_buyButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    QString symbol = ui->symbolLineEdit->text();
    unsigned int amount = ui->amountSpinBox->value();

    auto acc = bank->findAccount(accId);
    if (!acc) {
        QMessageBox::warning(this, "Error", "Account not found");
        return;
    }

    if (market->buyStock(acc->getId(), symbol.toStdString(), amount))
        QMessageBox::information(this, "Success", "Stock purchased");
    else
        QMessageBox::warning(this, "Error", "Purchase failed");
}

void StockMarketDialog::on_sellButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    QString symbol = ui->symbolLineEdit->text();
    unsigned int amount = ui->amountSpinBox->value();

    auto acc = bank->findAccount(accId);
    if (!acc) {
        QMessageBox::warning(this, "Error", "Account not found");
        return;
    }

    if (market->sellStock(acc->getId(), symbol.toStdString(), amount))
        QMessageBox::information(this, "Success", "Stock sold");
    else
        QMessageBox::warning(this, "Error", "Sell failed");
}
