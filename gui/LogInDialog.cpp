#include "LogInDialog.h"
#include "ui_LogInDialog.h"
#include "../headers/Authmanager.h"
#include "../headers/FileStorage.h"
#include <QMessageBox>

using namespace MiniBank;

LogInDialog::LogInDialog(FileStorage* storage, QWidget* parent)
    : QDialog(parent), ui(new Ui::LogInDialog), m_storage(storage), m_auth(new Authmanager()), m_userId(-1)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &LogInDialog::on_btnLogin_clicked);
    connect(ui->btnSignup, &QPushButton::clicked, this, &LogInDialog::on_btnSignup_clicked);
}

LogInDialog::~LogInDialog() {
    delete m_auth;
    delete ui;
}

void LogInDialog::on_btnLogin_clicked() {
    QString user = ui->usernameEdit->text().trimmed();
    QString pass = ui->passwordEdit->text();
    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Login", "Vul gebruikersnaam en wachtwoord in.");
        return;
    }
    std::string err;
    int uid = -1;
    bool ok = m_auth->login(user.toStdString(), pass.toStdString(), uid, err);
    if (ok) {
        m_userId = uid;
        accept();
    } else {
        QMessageBox::warning(this, "Login failed", QString::fromStdString(err));
    }
}

void LogInDialog::on_btnSignup_clicked() {
    QString user = ui->usernameEdit->text().trimmed();
    QString pass = ui->passwordEdit->text();
    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Signup", "Vul gebruikersnaam en wachtwoord in.");
        return;
    }
    std::string err;
    if (m_auth->signup(user.toStdString(), pass.toStdString(), err)) {
        QMessageBox::information(this, "Signup", "Account aangemaakt. Log nu in.");
    } else {
        QMessageBox::warning(this, "Signup failed", QString::fromStdString(err));
    }
}
