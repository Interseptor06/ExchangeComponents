//
// Created by martin on 15.06.22 г..
//

#ifndef ORDERBOOK_ORDERTREE_H
#define ORDERBOOK_ORDERTREE_H

#include <unordered_map>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstdint>
#include <map>
#include "OrderSide.h"
#include "Limit.h"

class OrderTree {
public:
    explicit OrderTree(Side newSide);
    OrderTree(const OrderTree&) noexcept = default;
    OrderTree(OrderTree&&) noexcept = default;

    [[nodiscard]] uint_fast64_t getVolume() const;
    [[nodiscard]] uint_fast64_t getNOrders() const;
    [[nodiscard]] uint_fast64_t getDepth() const;

    Limit* getLimit(uint_fast64_t LimitPrice);
    Order* getOrder(uint_fast64_t OrderID);

    bool limitExists(uint_fast64_t LimitPrice);
    bool orderExists(uint_fast64_t OrderID);

    Limit* maxPriceLimit();
    Limit* minPriceLimit();
    Limit* bestPriceLimit();

    uint_fast64_t maxPrice();
    uint_fast64_t minPrice();
    uint_fast64_t bestPrice();

    void createPrice(uint_fast64_t newPrice);
    void removePrice(uint_fast64_t oldPrice);

    void RemoveOrderByID(uint_fast64_t oldOrderID);
    void InsertOrder(Order& newOrder);

    // Returns volume at a better than given Price - Could be zero
    uint_fast64_t getBestVolume(uint_fast64_t Price);

private:
    Side TreeSide;
    uint_fast64_t Volume;
    uint_fast64_t nOrders;
    uint_fast64_t Depth;
    std::map<uint_fast64_t, Limit*>* priceTree; // <LimitPrice, Limit>
    std::unordered_map<uint_fast64_t, Limit*>* priceMap; // <LimitPrice, Limit>
    std::unordered_map<uint_fast64_t, Order*>* orderMap; // <OrderID, Order>
};


#endif //ORDERBOOK_ORDERTREE_H
