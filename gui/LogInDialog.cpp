#include "LogInDialog.h"
#include "ui_LogInDialog.h"
#include <QMessageBox>

LogInDialog::LogInDialog(AuthManager* auth, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog),
    authManager(auth)
{
    ui->setupUi(this);
    setWindowTitle("Bank Login");
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void LogInDialog::showMessage(const QString& msg) {
    QMessageBox::information(this, "Info", msg);
}

void LogInDialog::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if(authManager->login(username.toStdString(), password.toStdString())) {
        showMessage("Login successful!");
        emit loginSuccess();
        accept();
    } else {
        showMessage("Invalid username or password.");
    }
}

void LogInDialog::on_signupButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if(authManager->signup(username.toStdString(), password.toStdString())) {
        showMessage("Signup successful! You can now login.");
    } else {
        showMessage("Username already exists.");
    }
}
