// fluctuator.h
#ifndef FLUCTUATOR_H
#define FLUCTUATOR_H

#include <queue>
#include <string>

class Stock {
private:
    std::string symbol;
    double price;

public:
    Stock(std::string symbol, double initialPrice);
    std::string getSymbol() const;
    double getPrice() const;
    void updatePrice(double newPrice);
    void simulatePriceFluctuation();
};

// Simulate market fluctuations
void simulateMarketFluctuationsWithQueue(std::queue<Stock>& stockQueue);

#endif
