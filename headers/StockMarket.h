#ifndef STOCKMARKET_H
#define STOCKMARKET_H

#include <QObject>
#include <QThread>
#include <QString>
#include <map>
#include <mutex>
#include <random>

    namespace MiniBank {

struct Stock {
    std::string name;
    std::string symbol;
    double price;
    double volatility;
};

class StockMarket : public QObject {
    Q_OBJECT
public:
    explicit StockMarket(QObject* parent = nullptr);
    ~StockMarket();

    void startSimulation();
    void stopSimulation();

    std::vector<Stock> getStocks() const;
    bool buyStock(unsigned int accountId, const std::string& symbol, unsigned int amount);
    bool sellStock(unsigned int accountId, const std::string& symbol, unsigned int amount);

signals:
    void stockPriceUpdated(const std::string& symbol, double newPrice);

private:
    std::vector<Stock> stocks;
    QThread* workerThread;
    bool running;
    mutable std::mutex mtx;

    void simulatePrices();
};

}

#endif // STOCKMARKET_H
