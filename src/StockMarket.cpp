#include "../headers/StockMarket.h"
#include <random>

namespace MiniBank {

void StockMarket::simulateTick() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0.0, 1.0);
    for (auto &s : stocks) {
        double change = d(gen);
        s.price = std::max(0.01, s.price + change);
    }
}

} // namespace MiniBank
