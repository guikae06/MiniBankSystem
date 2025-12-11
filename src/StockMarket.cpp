#include "StockMarket.h"
#include <QTimer>
#include <chrono>
#include <thread>
#include <iostream>

namespace MiniBank {

StockMarket::StockMarket(QObject* parent)
    : QObject(parent), workerThread(nullptr), running(false)
{
    stocks.push_back({"Apple", "AAPL", 150.0, 0.02});
    stocks.push_back({"Google", "GOOG", 2800.0, 0.015});
    stocks.push_back({"Amazon", "AMZN", 3400.0, 0.017});
}

StockMarket::~StockMarket() {
    stopSimulation();
}

void StockMarket::startSimulation() {
    if (running) return;
    running = true;
    workerThread = QThread::create([this](){ simulatePrices(); });
    workerThread->start();
}

void StockMarket::stopSimulation() {
    if (!running) return;
    running = false;
    if (workerThread) {
        workerThread->quit();
        workerThread->wait();
        delete workerThread;
        workerThread = nullptr;
    }
}

std::vector<Stock> StockMarket::getStocks() const {
    std::lock_guard<std::mutex> lock(mtx);
    return stocks;
}

bool StockMarket::buyStock(unsigned int accountId, const std::string& symbol, unsigned int amount) {
    Q_UNUSED(accountId)
    Q_UNUSED(symbol)
    Q_UNUSED(amount)
    return true;
}

bool StockMarket::sellStock(unsigned int accountId, const std::string& symbol, unsigned int amount) {
    Q_UNUSED(accountId)
    Q_UNUSED(symbol)
    Q_UNUSED(amount)
    return true;
}

void StockMarket::simulatePrices() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    while (running) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            for (auto& s : stocks) {
                double change = s.price * s.volatility * dist(gen);
                s.price = std::max(1.0, s.price + change);
                emit stockPriceUpdated(s.symbol, s.price);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

} // namespace MiniBank
