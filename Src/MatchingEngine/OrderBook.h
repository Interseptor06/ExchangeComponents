//
// Created by martin on 15.06.22 г..
//

#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H

#include "OrderTree.h"
#include "Errors.h"
#include "Trade.h"
#include "utils.h"
#include <vector>
#include <cstdint>

struct TradeReport{
    explicit TradeReport(std::vector<Trade>* _trades): Trades(_trades) {};
    std::vector<Trade>* Trades;
};

class OrderBook {
public:
    OrderBook();

    uint_fast64_t getBestBid();
    uint_fast64_t getWorstBid();
    uint_fast64_t getBestAsk();
    uint_fast64_t getWorstAsk();

    uint_fast64_t getSpread();
    uint_fast64_t getMid();

    bool bidsAndAsksExist();

    uint_fast64_t getVolumeOnSide(Side _side);

    void DeleteOrder(uint_fast64_t OldOrderID);
    void AddOrder(Order &newOrder);
    void AddMarketOrder(Order &newOrder);
    void AddLimitOrder(Order &newOrder);
    void ModifyOrder(uint_fast64_t id, uint_fast64_t new_price, uint_fast64_t new_quantity);
    void ModifyQuantity(uint_fast64_t id, uint_fast64_t new_quantity);

    Order* FindOrder(uint_fast64_t id);

private:
    OrderTree* Bids; // Buys
    OrderTree* Asks; // Sells

    std::vector<TradeReport*>* Trades;
};


#endif //ORDERBOOK_ORDERBOOK_H
