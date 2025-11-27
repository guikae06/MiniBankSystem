#include "StockMarket.h"
#include <QRandomGenerator>
#include <QtMath>

StockMarket::StockMarket(QObject *parent): QObject(parent) {
    m_stocks["FKA"] = {"FKA","FakeAlpha", 100.0};
    m_stocks["FKB"] = {"FKB","FakeBeta", 50.0};
    m_stocks["FKC"] = {"FKC","FakeCorp", 200.0};
    connect(&m_timer, &QTimer::timeout, this, &StockMarket::tick);
}

void StockMarket::start(int intervalMs) {
    m_timer.start(intervalMs);
}

QList<StockInfo> StockMarket::stocks() const {
    return m_stocks.values();
}

double StockMarket::randomJitter() {
    double p = (QRandomGenerator::global()->bounded(-300,300))/100.0; // -3%..+3%
    return p/100.0;
}

void StockMarket::tick() {
    for (auto &s : m_stocks) {
        double jitter = randomJitter();
        s.price = qMax(0.01, s.price * (1.0 + jitter));
        emit priceUpdated(s.symbol, s.price);
    }
}
