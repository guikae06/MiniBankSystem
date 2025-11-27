#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../headers/StockMarket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(int userId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPriceUpdated(const QString &symbol, double price);
    void on_actionTransfer_triggered();
    void on_btnBuyStock_clicked();
    void on_btnSellStock_clicked();

private:
    Ui::MainWindow *ui;
    int m_userId;
    StockMarket *m_stockMarket;

};

#endif
