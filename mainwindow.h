#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void deposit();      // Slot voor deposit knop
    void withdraw();     // Slot voor withdraw knop
    void addInterest();  // Slot voor interest knop

private:
    Ui::MainWindow *ui;

    MiniBank::SavingsAccount* sa;   // Pointer naar SavingsAccount
    MiniBank::CheckingAccount* ca;  // Pointer naar CheckingAccount
};

#endif // MAINWINDOW_H
