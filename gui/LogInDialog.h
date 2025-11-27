#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui { class LogInDialog; }

class FileStorage;
class AuthManager;

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(FileStorage *storage, QWidget *parent = nullptr);
    ~LogInDialog();
    int authenticatedUserId() const { return m_userId; }

private slots:
    void on_btnLogin_clicked();
    void on_btnSignup_clicked();

private:
    Ui::LogInDialog *ui;
    FileStorage *m_storage;
    AuthManager *m_auth;
    int m_userId{-1};
};

#endif // LOGINDIALOG_H
