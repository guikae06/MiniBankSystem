#ifndef STOCKMARKET_H
#define STOCKMARKET_H

#include <string>
#include <vector>
#include <functional>

namespace MiniBank {

class StockMarket {
public:
    struct Stock { std::string symbol; double price; };

    StockMarket() = default;
    void simulateTick();
    std::vector<Stock> getStocks() const { return stocks; }

private:
    std::vector<Stock> stocks{{"FOO",100.0},{"BAR",50.0},{"ACME",10.0}};
};

} // namespace MiniBank

#endif // STOCKMARKET_H
