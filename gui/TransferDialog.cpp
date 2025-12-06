#include "TransferDialog.h"
#include "ui_TransferDialog.h"

TransferDialog::TransferDialog(QWidget* parent) : QDialog(parent), ui(new Ui::TransferDialog) {
    ui->setupUi(this);
}
TransferDialog::~TransferDialog() { delete ui; }
