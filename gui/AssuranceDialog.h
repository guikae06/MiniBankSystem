#ifndef ASSURANCEDIALOG_H
#define ASSURANCEDIALOG_H

#include <QDialog>
#include <QVector>
#include <QString>
#include "Bank.h"

namespace Ui {
class AssuranceDialog;
}

class AssuranceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssuranceDialog(MiniBank::Account* account, QWidget *parent = nullptr);
    ~AssuranceDialog();

    // ✅ Public so static array outside class can access it
    struct InsuranceItem {
        QString name;
        double price;
    };

private slots:
    void on_buyButton_clicked();
    void on_backButton_clicked();

private:
    void refreshOwnedInsurances();

    Ui::AssuranceDialog *ui;
    MiniBank::Account* account; // Logged-in account
    QVector<InsuranceItem> availableInsurances;
};

#endif // ASSURANCEDIALOG_H
