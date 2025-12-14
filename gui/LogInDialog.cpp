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

    loggedAccount = bank->loginUser(username, password);
    if (!loggedAccount) {
        QMessageBox::warning(this, "Error", "Invalid username or password");
        return;
    }

    // Pass the logged-in account to MainMenuDialog
    MainMenuDialog menu(bank, market, loggedAccount);
    menu.exec();
}

void LogInDialog::on_signupButton_clicked()
{
    std::string username = ui->usernameLineEdit->text().toStdString();
    std::string password = ui->passwordLineEdit->text().toStdString();

    loggedAccount = bank->createCheckingAccount(username);

    if (!bank->registerUser(username, password, loggedAccount)) {
        QMessageBox::warning(this, "Error", "Username already exists");
        return;
    }

    QMessageBox::information(this, "Success", "Successfully registered");

    // Pass the logged-in account to MainMenuDialog
    MainMenuDialog menu(bank, market, loggedAccount);
    menu.exec();
}
