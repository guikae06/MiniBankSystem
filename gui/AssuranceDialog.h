#ifndef ASSURANCEDIALOG_H
#define ASSURANCEDIALOG_H

#include <QDialog>
#include "Bank.h"

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
    void on_backButton_clicked();
    void on_accountIdSpinBox_valueChanged(int value);


private:
    void loadInsurances();
    void refreshOwnedInsurances();

    Ui::AssuranceDialog *ui;
    MiniBank::Bank* bank;

    struct Insurance {
        QString name;
        double price;
    };

    QVector<Insurance> availableInsurances;
};

#endif
