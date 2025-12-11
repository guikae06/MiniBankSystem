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
    explicit StockMarketDialog(MiniBank::Bank* bank, QWidget *parent = nullptr);
    ~StockMarketDialog();

private slots:
    void on_buyButton_clicked();
    void on_sellButton_clicked();
    void updateStockPrice(const std::string& symbol, double price);

private:
    Ui::StockMarketDialog *ui;
    MiniBank::Bank* bank;
};

#endif // STOCKMARKETDIALOG_H
