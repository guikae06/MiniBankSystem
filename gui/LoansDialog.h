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
    explicit LoansDialog(MiniBank::Bank* bank, QWidget *parent = nullptr);
    ~LoansDialog();

private slots:
    void on_requestLoanButton_clicked();
    void on_payLoanButton_clicked();

private:
    Ui::LoansDialog *ui;
    MiniBank::Bank* bank;
};

#endif // LOANSDIALOG_H
