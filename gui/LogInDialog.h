#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "../headers/AuthManager.h"

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(AuthManager* authManager, QWidget *parent = nullptr);
    ~LogInDialog();

signals:
    void loginSuccess();

private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();

private:
    Ui::LogInDialog *ui;
    AuthManager* authManager;
    void showMessage(const QString& msg);
};

#endif // LOGINDIALOG_H
