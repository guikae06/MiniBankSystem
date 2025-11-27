#include "LogInDialog.h"
#include "ui_LogInDialog.h"
#include "headers/FileStorage.h"
#include "headers/Authmanager.h"
#include <QMessageBox>

LogInDialog::LogInDialog(FileStorage *storage, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog),
    m_storage(storage)
{
    ui->setupUi(this);
    m_auth = new AuthManager(m_storage);
}

LogInDialog::~LogInDialog()
{
    delete m_auth;
    delete ui;
}

void LogInDialog::on_btnLogin_clicked()
{
    QString user = ui->usernameEdit->text().trimmed();
    QString pass = ui->passwordEdit->text();
    QString err;
    int uid;
    if (m_auth->login(user, pass, uid, err)) {
        m_userId = uid;
        accept();
    } else {
        QMessageBox::warning(this, "Login failed", err);
    }
}

void LogInDialog::on_btnSignup_clicked()
{
    QString user = ui->usernameEdit->text().trimmed();
    QString pass = ui->passwordEdit->text();
    QString err;
    if (!m_auth->signup(user, pass, err)) {
        QMessageBox::warning(this, "Signup failed", err);
    } else {
        QMessageBox::information(this, "Signup", "User created. You can now login.");
    }
}
