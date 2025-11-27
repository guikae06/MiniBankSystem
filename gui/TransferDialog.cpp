#include "TransferDialog.h"
#include "ui_TransferDialog.h"

TransferDialog::TransferDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TransferDialog) {
    ui->setupUi(this);
}

TransferDialog::~TransferDialog(){ delete ui; }

QString TransferDialog::fromAccount() const { return ui->fromEdit->text(); }
QString TransferDialog::toAccount() const { return ui->toEdit->text(); }
double TransferDialog::amount() const { return ui->amountEdit->text().toDouble(); }

void TransferDialog::on_btnTransfer_clicked() { accept(); }
