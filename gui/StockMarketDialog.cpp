#include "StockMarketDialog.h"
#include "ui_StockMarketDialog.h"
#include <QMessageBox>

StockMarketDialog::StockMarketDialog(MiniBank::Account* acc,
                                     MiniBank::StockMarket* m,
                                     QWidget *parent)
    : QDialog(parent),
    ui(new Ui::StockMarketDialog),
    account(acc),
    market(m)
{
    ui->setupUi(this);


    ui->stockTextEdit->setText("Market ready");

    // ✅ FIX: back button actually closes the dialog
    connect(ui->backButton, &QPushButton::clicked,
            this, &QDialog::accept);
}

StockMarketDialog::~StockMarketDialog()
{
    delete ui;
}

void StockMarketDialog::on_buyButton_clicked()
{
    QString symbol = ui->symbolLineEdit->text();
    unsigned int amount = ui->amountSpinBox->value();

    if (market->buyStock(account->getId(),
                         symbol.toStdString(),
                         amount))
        QMessageBox::information(this, "Success", "Stock purchased");
    else
        QMessageBox::warning(this, "Error", "Purchase failed");
}

void StockMarketDialog::on_sellButton_clicked()
{
    QString symbol = ui->symbolLineEdit->text();
    unsigned int amount = ui->amountSpinBox->value();

    if (market->sellStock(account->getId(),
                          symbol.toStdString(),
                          amount))
        QMessageBox::information(this, "Success", "Stock sold");
    else
        QMessageBox::warning(this, "Error", "Sell failed");
}
