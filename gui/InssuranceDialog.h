#ifndef INSSURANCEDIALOG_H
#define INSSURANCEDIALOG_H

#include <QDialog>
#include <QVector>
#include <QString>
#include "../headers/Account.h"

namespace Ui {
class InssuranceDialog;
}

class InssuranceDialog : public QDialog
{
    Q_OBJECT

public:
    struct InsuranceItem {
        QString name;
        double price;
    };

    explicit InssuranceDialog(MiniBank::Account* acc, QWidget *parent = nullptr);
    ~InssuranceDialog();

private slots:
    void on_buyButton_clicked();
    void on_backButton_clicked();

private:
    Ui::InssuranceDialog *ui;
    MiniBank::Account* account;
    QVector<InsuranceItem> availableInsurances;

    void refreshOwnedInsurances();
};

#endif // INSSURANCEDIALOG_H
