#include "StockMarketDialog.h"
#include "ui_StockMarketDialog.h"
#include <QString>
#include <QMessageBox>

StockMarketDialog::StockMarketDialog(MiniBank::Bank* b, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockMarketDialog),
    bank(b)
{
    ui->setupUi(this);
    setWindowTitle("Stock Market");

    auto& market = bank->getStockMarket();
    connect(&market, &MiniBank::StockMarket::stockPriceUpdated, this, &StockMarketDialog::updateStockPrice);
    market.startSimulation();
}

StockMarketDialog::~StockMarketDialog()
{
    bank->getStockMarket().stopSimulation();
    delete ui;
}

void StockMarketDialog::updateStockPrice(const std::string& symbol, double price)
{
    QString line = QString::fromStdString(symbol) + ": " + QString::number(price);
    ui->stockTextEdit->append(line);
}

void StockMarketDialog::on_buyButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    QString symbol = ui->symbolLineEdit->text();
    unsigned int amount = ui->amountSpinBox->value();

    if(bank->getStockMarket().buyStock(accId, symbol.toStdString(), amount))
        QMessageBox::information(this, "Stock", "Stock purchase successful.");
    else
        QMessageBox::warning(this, "Stock", "Purchase failed.");
}

void StockMarketDialog::on_sellButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    QString symbol = ui->symbolLineEdit->text();
    unsigned int amount = ui->amountSpinBox->value();

    if(bank->getStockMarket().sellStock(accId, symbol.toStdString(), amount))
        QMessageBox::information(this, "Stock", "Stock sale successful.");
    else
        QMessageBox::warning(this, "Stock", "Sale failed.");
}
