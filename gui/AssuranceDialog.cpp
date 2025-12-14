#include "AssuranceDialog.h"
#include "ui_AssuranceDialog.h"
#include <QMessageBox>

struct InsuranceItem {
    QString name;
    double price;
};

static const InsuranceItem INSURANCES[] = {
    {"Health Insurance", 100.0},
    {"Car Insurance", 150.0},
    {"Home Insurance", 200.0}
};

AssuranceDialog::AssuranceDialog(MiniBank::Bank* b, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AssuranceDialog),
    bank(b)
{
    ui->setupUi(this);

    for (const auto& ins : INSURANCES) {
        ui->insuranceComboBox->addItem(
            ins.name + " (€" + QString::number(ins.price) + ")"
            );
    }

    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);
}

AssuranceDialog::~AssuranceDialog()
{
    delete ui;
}

void AssuranceDialog::on_buyButton_clicked()
{
    unsigned int accId = ui->accountIdSpinBox->value();
    auto acc = bank->findAccount(accId);

    if (!acc) {
        QMessageBox::warning(this, "Error", "Account not found");
        return;
    }

    int index = ui->insuranceComboBox->currentIndex();
    auto insurance = INSURANCES[index];

    if (!acc->buyInsurance(insurance.name.toStdString(), insurance.price)) {
        QMessageBox::warning(this, "Error", "Cannot buy insurance");
        return;
    }

    QMessageBox::information(this, "Success", "Insurance purchased");
    refreshOwnedInsurances();
}

void AssuranceDialog::refreshOwnedInsurances()
{
    ui->ownedListWidget->clear();

    unsigned int accId = ui->accountIdSpinBox->value();
    auto acc = bank->findAccount(accId);
    if (!acc) return;

    for (const auto& ins : acc->getInsurances()) {
        ui->ownedListWidget->addItem(
            QString::fromStdString(ins.name) +
            " (€" + QString::number(ins.price) + ")"
            );
    }
}

// ===== MISSING SLOTS FIX =====
void AssuranceDialog::on_backButton_clicked()
{
    accept(); // closes dialog and returns to main menu
}

void AssuranceDialog::on_accountIdSpinBox_valueChanged(int)
{
    refreshOwnedInsurances();
}
