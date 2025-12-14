#include "StockMarket.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>

namespace MiniBank {

StockMarket::StockMarket(QObject* parent)
    : QObject(parent), workerThread(nullptr), running(false)
{
    // 10 stocks
    stocks.push_back({"Apple", "AAPL", 150.0, 0.02});
    stocks.push_back({"Google", "GOOG", 2800.0, 0.015});
    stocks.push_back({"Amazon", "AMZN", 3400.0, 0.017});
    stocks.push_back({"Microsoft", "MSFT", 300.0, 0.018});
    stocks.push_back({"Tesla", "TSLA", 900.0, 0.03});
    stocks.push_back({"Facebook", "META", 350.0, 0.02});
    stocks.push_back({"Netflix", "NFLX", 550.0, 0.025});
    stocks.push_back({"Nvidia", "NVDA", 500.0, 0.03});
    stocks.push_back({"Intel", "INTC", 55.0, 0.015});
    stocks.push_back({"AMD", "AMD", 100.0, 0.02});
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
        std::this_thread::sleep_for(std::chrono::seconds(10)); // 🔹 update every 10s
    }
}

} // namespace MiniBank
