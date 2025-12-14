#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"

namespace Ui {
class TransferDialog;
}

class TransferDialog : public QDialog
{
    Q_OBJECT

public:
    // ✅ Constructor takes the logged-in account + bank
    explicit TransferDialog(MiniBank::Account* senderAccount, MiniBank::Bank* bank, QWidget *parent = nullptr);
    ~TransferDialog();

private slots:
    void on_transferButton_clicked();
    void on_backButton_clicked();

private:
    Ui::TransferDialog *ui;
    MiniBank::Account* sender; // Logged-in account
    MiniBank::Bank* bank;      // For finding other accounts
};

#endif // TRANSFERDIALOG_H
