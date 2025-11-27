#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>

namespace Ui { class TransferDialog; }

class TransferDialog : public QDialog {
    Q_OBJECT
public:
    explicit TransferDialog(QWidget *parent = nullptr);
    ~TransferDialog();
    QString fromAccount() const;
    QString toAccount() const;
    double amount() const;

private slots:
    void on_btnTransfer_clicked();

private:
    Ui::TransferDialog *ui;
};

#endif
