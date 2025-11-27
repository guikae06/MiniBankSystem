#ifndef STOCKMARKET_H
#define STOCKMARKET_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QList>

struct StockInfo { QString symbol; QString name; double price; };

class StockMarket : public QObject {
    Q_OBJECT
public:
    explicit StockMarket(QObject *parent=nullptr);
    void start(int intervalMs=2000);
    QList<StockInfo> stocks() const;

signals:
    void priceUpdated(const QString &symbol, double price);

public slots:
    void tick();

private:
    QTimer m_timer;
    QMap<QString, StockInfo> m_stocks;
    double randomJitter();
};

#endif
