#ifndef MAINMENUDIALOG_H
#define MAINMENUDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"
#include "../headers/StockMarket.h"

namespace Ui {
class MainMenuDialog;
}

class MainMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenuDialog(MiniBank::Bank* bank,
                            MiniBank::StockMarket* market,
                            MiniBank::Account* account,
                            QWidget *parent = nullptr);
    ~MainMenuDialog();

private slots:
    void on_depositWithdrawButton_clicked();
    void on_loansButton_clicked();
    void on_inssuranceButton_clicked();
    void on_stockMarketButton_clicked();


private:
    Ui::MainMenuDialog *ui;
    MiniBank::Bank* bank;
    MiniBank::StockMarket* market;
    MiniBank::Account* account; // ✅ Add logged-in account here
};

#endif
