#include <QApplication>

#include "mainwindow.h"
#include "../headers/Bank.h"
#include "../headers/FileStorage.h"
#include "../headers/StockMarket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MiniBank::Bank bank;
    MiniBank::FileStorage storage("bankdata.txt");
    MiniBank::StockMarket market;

    MainWindow w(&bank, &storage, &market);
    w.show();

    return a.exec();
}
