//
// Created by martin on 18.06.22 г..
//

#ifndef ORDERBOOK_TRADE_H
#define ORDERBOOK_TRADE_H

#include "Order.h"
#include <cstdint>
#include <ostream>

class Trade {
public:

    Trade(unsigned long timeStamp, uint_fast64_t price, uint_fast64_t quantity, uint_fast64_t buyer,
          uint_fast64_t seller, uint_fast64_t buyOrderId, uint_fast64_t sellOrderId, uint_fast64_t instrumentID);
    Trade(Trade&&) noexcept = default;
    Trade(const Trade&) noexcept = default;
    ~Trade() = default;

    [[nodiscard]] inline unsigned long getTimeStamp() const {
        return TimeStamp;
    }
    [[nodiscard]] inline uint_fast64_t getPrice() const {
        return Price;
    }
    [[nodiscard]] inline uint_fast64_t getQuantity() const {
        return Quantity;
    }
    [[nodiscard]] inline uint_fast64_t getBuyer() const {
        return Buyer;
    }
    [[nodiscard]] inline uint_fast64_t getSeller() const {
        return Seller;
    }
    [[nodiscard]] inline uint_fast64_t getBuyOrderId() const {
        return buyOrderID;
    }
    [[nodiscard]] inline uint_fast64_t getSellOrderId() const {
        return sellOrderID;
    }
    [[nodiscard]] inline uint_fast64_t getInstrumentId() const {
        return InstrumentID;
    }

    friend std::ostream &operator<<(std::ostream &os, const Trade &trade);

private:
    unsigned long TimeStamp;
    uint_fast64_t Price;
    uint_fast64_t Quantity;
    uint_fast64_t Buyer; // Buyer customerID
    uint_fast64_t Seller; // Seller customerID

    uint_fast64_t buyOrderID;
    uint_fast64_t sellOrderID;

    uint_fast64_t InstrumentID;
};

Trade::Trade(unsigned long timeStamp,
             uint_fast64_t price,
             uint_fast64_t quantity,
             uint_fast64_t buyer,
             uint_fast64_t seller,
             uint_fast64_t buyOrderId,
             uint_fast64_t sellOrderId,
             uint_fast64_t instrumentID) : TimeStamp(timeStamp), Price(price),
             Quantity(quantity), Buyer(buyer),
             Seller(seller), buyOrderID(buyOrderId),
             sellOrderID(sellOrderId), InstrumentID(instrumentID) {}

std::ostream &operator<<(std::ostream &os, const Trade &trade) {
    os << "TimeStamp: " << trade.TimeStamp << " Price: " << trade.Price << " Quantity: " << trade.Quantity << " Buyer: "
       << trade.Buyer << " Seller: " << trade.Seller << " buyOrderID: " << trade.buyOrderID << " sellOrderID: "
       << trade.sellOrderID;
    return os;
}

#endif //ORDERBOOK_TRADE_H
