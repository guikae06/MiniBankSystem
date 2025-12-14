#include <QApplication>
#include "LogInDialog.h"
#include "../headers/Bank.h"
#include "../headers/StockMarket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MiniBank::Bank bank;
    MiniBank::StockMarket market;

    LogInDialog login(&bank, &market);
    login.exec();

    return a.exec();
}
