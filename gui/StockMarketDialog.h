#ifndef STOCKMARKETDIALOG_H
#define STOCKMARKETDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"
#include "../headers/StockMarket.h"

namespace Ui {
class StockMarketDialog;
}

class StockMarketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockMarketDialog(MiniBank::Bank* bank,
                               MiniBank::StockMarket* market,
                               QWidget *parent = nullptr);
    ~StockMarketDialog();

private slots:
    void on_buyButton_clicked();
    void on_sellButton_clicked();

private:
    Ui::StockMarketDialog *ui;
    MiniBank::Bank* bank;
    MiniBank::StockMarket* market;
};

#endif
