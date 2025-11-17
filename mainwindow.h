#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "Bank.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace MiniBank;

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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Bank> bank;
    Account* defaultAccount{nullptr};
};

#endif // MAINWINDOW_H
