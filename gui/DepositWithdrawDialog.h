#ifndef DEPOSITWITHDRAWDIALOG_H
#define DEPOSITWITHDRAWDIALOG_H

#include <QDialog>
#include "../headers/Account.h"

namespace Ui {
class DepositWithdrawDialog;
}

class DepositWithdrawDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DepositWithdrawDialog(MiniBank::Account* account, QWidget *parent = nullptr);
    ~DepositWithdrawDialog();

private slots:
    void on_depositBtn_clicked();
    void on_withdrawBtn_clicked();

private:
    Ui::DepositWithdrawDialog *ui;
    MiniBank::Account* account; // ✅ store logged-in account
};

#endif
