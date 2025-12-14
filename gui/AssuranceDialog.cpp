#include "AssuranceDialog.h"
#include "ui_AssuranceDialog.h"
#include <QMessageBox>

// ✅ Define available insurances outside class (now allowed)
static const AssuranceDialog::InsuranceItem INSURANCES[] = {
    {"Health Insurance", 100.0},
    {"Car Insurance", 150.0},
    {"Home Insurance", 200.0}
};

AssuranceDialog::AssuranceDialog(MiniBank::Account* acc, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AssuranceDialog),
    account(acc)
{
    ui->setupUi(this);

    // Populate combo box and availableInsurances vector
    for (const auto& ins : INSURANCES) {
        ui->insuranceComboBox->addItem(ins.name + " (€" + QString::number(ins.price) + ")");
        availableInsurances.append(ins);
    }

    // Back button closes dialog
    connect(ui->backButton, &QPushButton::clicked, this, &QDialog::accept);

    // Show owned insurances
    refreshOwnedInsurances();
}

AssuranceDialog::~AssuranceDialog()
{
    delete ui;
}

void AssuranceDialog::on_buyButton_clicked()
{
    if (!account) {
        QMessageBox::warning(this, "Error", "No account available");
        return;
    }

    int index = ui->insuranceComboBox->currentIndex();
    if (index < 0 || index >= availableInsurances.size()) return;

    auto insurance = availableInsurances[index];

    if (!account->buyInsurance(insurance.name.toStdString(), insurance.price)) {
        QMessageBox::warning(this, "Error", "Cannot buy insurance (insufficient funds)");
        return;
    }

    QMessageBox::information(this, "Success", "Insurance purchased");
    refreshOwnedInsurances();
}

void AssuranceDialog::refreshOwnedInsurances()
{
    if (!account) return;

    ui->ownedListWidget->clear();
    for (const auto& ins : account->getInsurances()) {
        ui->ownedListWidget->addItem(QString::fromStdString(ins.name) +
                                     " (€" + QString::number(ins.price) + ")");
    }
}

void AssuranceDialog::on_backButton_clicked()
{
    accept(); // closes dialog
}
