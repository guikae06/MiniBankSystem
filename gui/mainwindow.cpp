#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/DBManager.h"
#include "../include/Bank.h"
#include "../include/CheckingAccount.h"
#include "../include/SavingsAccount.h"
#include <QChartView>
#include <QLineSeries>
#include <QtCharts>
#include <QMessageBox>
#include "TransferDialog.h"

using namespace QtCharts;
using namespace MiniBank;

MainWindow::MainWindow(int userId, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_userId(userId), m_db(DBManager::database())
{
    ui->setupUi(this);

    // start stock market
    m_stockMarket = new StockMarket(this);
    connect(m_stockMarket, &StockMarket::priceUpdated, this, &MainWindow::onPriceUpdated);
    m_stockMarket->start(2000);

    // setup chart area (simple)
    QChart *chart = new QChart();
    QChartView *view = new QChartView(chart);
    ui->stockChartLayout->addWidget(view);

    // fill stock list
    auto s = m_stockMarket->stocks();
    for (auto &si : s) {
        ui->stockList->addItem(si.symbol + " - " + si.name + " : " + QString::number(si.price));
    }

    // hook transfer action
    connect(ui->actionTransfer, &QAction::triggered, this, &MainWindow::on_actionTransfer_triggered);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onPriceUpdated(const QString &symbol, double price) {
    // update list quickly (inefficient but fine for demo)
    for (int i=0;i<ui->stockList->count();++i) {
        QString t = ui->stockList->item(i)->text();
        if (t.startsWith(symbol)) {
            ui->stockList->item(i)->setText(symbol + " - " + t.split(" - ").at(1).split(" : ").at(0) + " : " + QString::number(price));
            break;
        }
    }
}

void MainWindow::on_actionTransfer_triggered() {
    TransferDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QString from = dlg.fromAccount();
        QString to = dlg.toAccount();
        double amount = dlg.amount();
        std::string err;
        // call Bank object (you might have one in MainWindow or global)
        // For demo: create a Bank object and call transfer:
        Bank b;
        bool ok = b.transfer(from.toStdString(), to.toStdString(), amount, err, m_db);
        if (!ok) QMessageBox::warning(this, "Transfer failed", QString::fromStdString(err));
        else QMessageBox::information(this, "Transfer", "Success");
    }
}

void MainWindow::on_btnBuyStock_clicked() {
    // implement buy: reduce cash account, update portfolio table, insert transaction
}

void MainWindow::on_btnSellStock_clicked() {
    // implement sell
}
