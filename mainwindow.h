#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "MiniBank.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void deposit();
    void withdraw();
    void addInterest();
    void refreshDisplay();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<MiniBank::MiniBank> bank;
    MiniBank::Account* currentAccount{nullptr};
    std::string currentAccountId;
};

#endif // MAINWINDOW_H
