#ifndef STOCKMARKETDIALOG_H
#define STOCKMARKETDIALOG_H

#include <QDialog>
#include <QTimer>
#include <map>
#include "../headers/Account.h"
#include "../headers/StockMarket.h"

namespace Ui {
class StockMarketDialog;
}

class StockMarketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockMarketDialog(MiniBank::Account* account,
                               MiniBank::StockMarket* market,
                               QWidget *parent = nullptr);
    ~StockMarketDialog();

private slots:
    void on_buyButton_clicked();
    void on_sellButton_clicked();
    void updateStockPrice(const std::string& symbol, double price);

private:
    void populateStockTable();
    void updatePortfolioTable();

    Ui::StockMarketDialog *ui;
    MiniBank::Account* account;
    MiniBank::StockMarket* market;
    std::map<std::string, unsigned int> portfolio; // symbol -> shares
};

#endif
