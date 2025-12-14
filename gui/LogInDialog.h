#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"
#include "../headers/StockMarket.h"

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(MiniBank::Bank* bank,
                         MiniBank::StockMarket* market,
                         QWidget *parent = nullptr);
    ~LogInDialog();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LogInDialog *ui;
    MiniBank::Bank* bank;
    MiniBank::StockMarket* market;
};

#endif // LOGINDIALOG_H
