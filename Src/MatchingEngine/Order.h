//
// Created by martin on 14.06.22 г..
//

#pragma once

#include "Limit.h"
#include "OrderSide.h"
#include "OrderType.h"
#include "OrderTimeInForce.h"
#include <cstdint>
#include <stdexcept>

// Forward Declaration to avoid "XXX doesn't name a type style errors"
class Limit;
class OrderBook;


class Order {
public:
    Order(long Timestamp,
          Side Side,
          OrderType Type,
          uint_fast64_t Quantity,
          uint_fast64_t LimitPrice,
          uint_fast64_t OrderID,
          uint_fast64_t CustomerID,
          uint_fast64_t InstrumentID);
    Order(const Order&) noexcept = default;
    Order(Order&&) noexcept = default;

    virtual ~Order() = default;

    [[nodiscard]] long getTimestamp() const;
    [[nodiscard]] Side getSide() const;
    [[nodiscard]] OrderType getClass() const;
    [[nodiscard]] uint_fast64_t getInitialQuantity() const;
    [[nodiscard]] uint_fast64_t getRemainingQuantity() const;
    [[nodiscard]] uint_fast64_t getLimitPrice() const;
    [[nodiscard]] uint_fast64_t getOrderId() const;
    [[nodiscard]] uint_fast64_t getCustomerId() const;
    [[nodiscard]] uint_fast64_t getInstrumentId() const;

    void setRemainingQuantity(uint_fast64_t mRemainingQuantity);

    [[nodiscard]] Order *getNextOrder() const;
    [[nodiscard]] Order *getPreviousOrder() const;
    [[nodiscard]] Limit *getParentLimit() const;

    void setNextOrder(Order *nextOrder);
    void setPreviousOrder(Order *previousOrder);
    void setParentLimit(Limit *parentLimit);

    void setMLimitPrice(uint_fast64_t mLimitPrice);

    Order& operator=(const Order&) noexcept = default;
    Order& operator=(Order&&) noexcept = default;


private:
    long m_Timestamp;
    Side m_Side;
    OrderType m_Type; // Market Or Limit // Todo: Fix Name
    uint_fast64_t  m_InitialQuantity;
    uint_fast64_t m_RemainingQuantity;
    uint_fast64_t m_LimitPrice; // in cents
    uint_fast64_t m_OrderID;
    uint_fast64_t m_CustomerID;
    uint_fast64_t m_InstrumentID;

    OrderTimeInForce TimeInForce; // TODO: Add to constructor and fix everywhere else
    uint_fast64_t StopPrice; // Todo: Add and Fix


    Order* PreviousOrder;
    Order* NextOrder;

    Limit* ParentLimit;
};
