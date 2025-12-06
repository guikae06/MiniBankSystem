#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui { class LogInDialog; }
namespace MiniBank { class Authmanager; class FileStorage; }

class LogInDialog : public QDialog {
    Q_OBJECT
public:
    explicit LogInDialog(MiniBank::FileStorage* storage, QWidget* parent = nullptr);
    ~LogInDialog();
    int authenticatedUserId() const { return m_userId; }

private slots:
    void on_btnLogin_clicked();
    void on_btnSignup_clicked();

private:
    Ui::LogInDialog* ui;
    MiniBank::FileStorage* m_storage;
    MiniBank::Authmanager* m_auth;
    int m_userId{-1};
};

#endif // LOGINDIALOG_H
