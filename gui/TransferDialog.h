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
    explicit TransferDialog(MiniBank::Bank* bank, QWidget *parent = nullptr);
    ~TransferDialog();

private slots:
    void on_transferButton_clicked();

private:
    Ui::TransferDialog *ui;
    MiniBank::Bank* bank;
};

#endif // TRANSFERDIALOG_H
