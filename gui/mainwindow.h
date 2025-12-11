#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QListWidget>

// Include full definitions
#include "../headers/Bank.h"
#include "../headers/FileStorage.h"
#include "../headers/StockMarket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(MiniBank::Bank* bank,
                        MiniBank::FileStorage* storage,
                        MiniBank::StockMarket* market,
                        QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_depositBtn_clicked();
    void on_withdrawBtn_clicked();

private:
    void refreshAccountList();

    Ui::MainWindow* ui;

    MiniBank::Bank* bank_;
    MiniBank::FileStorage* storage_;
    MiniBank::StockMarket* market_;
};

#endif // MAINWINDOW_H
