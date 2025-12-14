#include "LogInDialog.h"
#include "ui_LogInDialog.h"
#include "MainMenuDialog.h"
#include <QMessageBox>

LogInDialog::LogInDialog(MiniBank::Bank* b,
                         MiniBank::StockMarket* m,
                         QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LogInDialog),
    bank(b),
    market(m)
{
    ui->setupUi(this);
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void LogInDialog::on_loginButton_clicked()
{
    std::string username = ui->usernameLineEdit->text().toStdString();
    std::string password = ui->passwordLineEdit->text().toStdString();

    MiniBank::Account* acc = bank->loginUser(username, password);
    if (!acc) {
        QMessageBox::warning(this, "Error", "Invalid username or password");
        return;
    }

    MainMenuDialog menu(bank, market);
    menu.exec();
}

void LogInDialog::on_signupButton_clicked()
{
    std::string username = ui->usernameLineEdit->text().toStdString();
    std::string password = ui->passwordLineEdit->text().toStdString();

    MiniBank::Account* acc = bank->createCheckingAccount(username);

    if (!bank->registerUser(username, password, acc)) {
        QMessageBox::warning(this, "Error", "Username already exists");
        return;
    }

    QMessageBox::information(this, "Success", "Successfully registered");

    MainMenuDialog menu(bank, market);
    menu.exec();
}
