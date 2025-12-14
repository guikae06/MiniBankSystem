#ifndef LOANSDIALOG_H
#define LOANSDIALOG_H

#include <QDialog>
#include "../headers/Account.h"

namespace Ui {
class LoansDialog;
}

class LoansDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoansDialog(MiniBank::Account* account, QWidget *parent = nullptr);
    ~LoansDialog();

private slots:
    void on_requestLoanButton_clicked();
    void on_payLoanButton_clicked();
    void on_backButton_clicked();

private:
    void refreshLoans();

    Ui::LoansDialog *ui;
    MiniBank::Account* account; // Logged-in account
};

#endif // LOANSDIALOG_H
