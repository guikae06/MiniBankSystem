#include "StockMarketDialog.h"
#include "ui_StockMarketDialog.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QString>
#include <algorithm>

StockMarketDialog::StockMarketDialog(MiniBank::Account* acc,
                                     MiniBank::StockMarket* mkt,
                                     QWidget *parent)
    : QDialog(parent),
    ui(new Ui::StockMarketDialog),
    account(acc),
    market(mkt)
{
    ui->setupUi(this);

    populateStockTable();
    updatePortfolioTable();

    connect(market, &MiniBank::StockMarket::stockPriceUpdated,
            this, &StockMarketDialog::updateStockPrice);

    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);

    market->startSimulation();
}

StockMarketDialog::~StockMarketDialog()
{
    market->stopSimulation();
    delete ui;
}

void StockMarketDialog::populateStockTable()
{
    auto stocks = market->getStocks();
    ui->stocksTable->setRowCount(static_cast<int>(stocks.size()));
    ui->stocksTable->setColumnCount(3);

    QStringList headers;
    headers << "Name" << "Symbol" << "Price (€)";
    ui->stocksTable->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < static_cast<int>(stocks.size()); ++row) {
        const auto& s = stocks[row];
        ui->stocksTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s.name)));
        ui->stocksTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s.symbol)));
        ui->stocksTable->setItem(row, 2, new QTableWidgetItem(QString::number(s.price, 'f', 2)));
    }
}

void StockMarketDialog::updateStockPrice(const std::string& symbol, double price)
{
    // Update stocks table
    for (int row = 0; row < ui->stocksTable->rowCount(); ++row) {
        auto item = ui->stocksTable->item(row, 1);
        if (item && item->text() == QString::fromStdString(symbol)) {
            ui->stocksTable->item(row, 2)->setText(QString::number(price, 'f', 2));
            break;
        }
    }

    // Update portfolio table
    updatePortfolioTable();
}

void StockMarketDialog::updatePortfolioTable()
{
    ui->portfolioTable->clear();
    ui->portfolioTable->setColumnCount(3);
    QStringList headers;
    headers << "Symbol" << "Shares Owned" << "Current Value (€)";
    ui->portfolioTable->setHorizontalHeaderLabels(headers);
    ui->portfolioTable->setRowCount(static_cast<int>(portfolio.size()));

    int row = 0;
    for (auto& pair : portfolio) {
        QString symbol = QString::fromStdString(pair.first);
        unsigned int shares = pair.second;

        // Find current price
        double price = 0.0;
        auto stocks = market->getStocks();
        auto it = std::find_if(stocks.begin(), stocks.end(),
                               [&](const MiniBank::Stock& s){ return s.symbol == pair.first; });
        if (it != stocks.end()) price = it->price;

        ui->portfolioTable->setItem(row, 0, new QTableWidgetItem(symbol));
        ui->portfolioTable->setItem(row, 1, new QTableWidgetItem(QString::number(shares)));
        ui->portfolioTable->setItem(row, 2, new QTableWidgetItem(QString::number(shares * price, 'f', 2)));

        ++row;
    }
}

void StockMarketDialog::on_buyButton_clicked()
{
    int row = ui->stocksTable->currentRow();
    if (row < 0) return;

    QString symbol = ui->stocksTable->item(row, 1)->text();
    double price = ui->stocksTable->item(row, 2)->text().toDouble();

    if (account->getBalance() < price) {
        QMessageBox::warning(this, "Error", "Not enough funds to buy stock.");
        return;
    }

    account->withdraw(price);
    portfolio[symbol.toStdString()] += 1;
    updatePortfolioTable();

    QMessageBox::information(this, "Success",
                             QString("Bought 1 share of %1 for €%2").arg(symbol).arg(price));
}

void StockMarketDialog::on_sellButton_clicked()
{
    int row = ui->stocksTable->currentRow();
    if (row < 0) return;

    QString symbol = ui->stocksTable->item(row, 1)->text();
    if (portfolio[symbol.toStdString()] == 0) {
        QMessageBox::warning(this, "Error", "No shares to sell.");
        return;
    }

    double price = ui->stocksTable->item(row, 2)->text().toDouble();

    portfolio[symbol.toStdString()] -= 1;
    account->deposit(price);
    updatePortfolioTable();

    QMessageBox::information(this, "Success",
                             QString("Sold 1 share of %1 for €%2").arg(symbol).arg(price));
}
