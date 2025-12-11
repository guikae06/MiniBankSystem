#ifndef ASSURANCEDIALOG_H
#define ASSURANCEDIALOG_H

#include <QDialog>
#include "../headers/Bank.h"

namespace Ui {
class AssuranceDialog;
}

class AssuranceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssuranceDialog(MiniBank::Bank* bank, QWidget *parent = nullptr);
    ~AssuranceDialog();

private slots:
    void on_buyButton_clicked();

private:
    Ui::AssuranceDialog *ui;
    MiniBank::Bank* bank;
    void showMessage(const QString& msg);
};

#endif // ASSURANCEDIALOG_H
