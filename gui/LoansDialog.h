#ifndef LOANSDIALOG_H
#define LOANSDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"

namespace Ui {
class LoansDialog;
}

class LoansDialog : public QDialog
{
    Q_OBJECT

public:
    // ✅ Constructor takes logged-in Account directly
    explicit LoansDialog(MiniBank::Account* account, QWidget *parent = nullptr);
    ~LoansDialog();

private slots:
    void on_requestLoanButton_clicked();
    void on_payLoanButton_clicked();
    void on_backButton_clicked();

private:
    Ui::LoansDialog *ui;
    MiniBank::Account* account; // Logged-in account
};

#endif // LOANSDIALOG_H
