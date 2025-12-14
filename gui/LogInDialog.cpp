#include "LogInDialog.h"
#include "ui_LogInDialog.h"
#include "MainMenuDialog.h"

LogInDialog::LogInDialog(MiniBank::Bank* b,
                         MiniBank::StockMarket* m,
                         QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LogInDialog),
    bank(b),
    market(m)
{
    ui->setupUi(this);

    // Disable signup button completely
    ui->signupButton->setEnabled(false);
    ui->signupButton->hide();
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

// --------------------
// LOGIN (USERNAME ONLY, NO PASSWORD CHECK)
// --------------------
void LogInDialog::on_loginButton_clicked()
{
    std::string username = ui->usernameLineEdit->text().toStdString();
    if (username.empty()) {
        username = "DefaultUser";
    }

    MiniBank::Account* account = nullptr;

    // Try to find existing account by username
    auto accounts = bank->getAccounts();
    for (auto acc : accounts) {
        if (acc->getOwnerName() == username) {
            account = acc;
            break;
        }
    }

    // If account does not exist, create new checking account
    if (!account) {
        account = bank->createCheckingAccount(username, 1000.0); // optional starting balance
    }

    // Open main menu
    hide();
    MainMenuDialog menu(bank, market, account);
    menu.exec();
    show();
}
