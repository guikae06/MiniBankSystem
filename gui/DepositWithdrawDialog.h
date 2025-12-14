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
    void on_accountList_currentRowChanged(int row); // 🔥 account selection changed

private:
    void refreshAccounts();
    void refreshHistory();

    Ui::DepositWithdrawDialog *ui;
    MiniBank::Account* account;
    std::vector<MiniBank::Account*> allAccounts; // 🔥 for all accounts (if multiple)
};

#endif
