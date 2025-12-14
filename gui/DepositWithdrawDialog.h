#ifndef DEPOSITWITHDRAWDIALOG_H
#define DEPOSITWITHDRAWDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"

namespace Ui {
class DepositWithdrawDialog;
}

class DepositWithdrawDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DepositWithdrawDialog(MiniBank::Bank* bank, QWidget *parent = nullptr);

    ~DepositWithdrawDialog();

private slots:
    void on_depositBtn_clicked();
    void on_withdrawBtn_clicked();

private:
    Ui::DepositWithdrawDialog *ui;
    MiniBank::Bank* bank;
};

#endif // DEPOSITWITHDRAWDIALOG_H
