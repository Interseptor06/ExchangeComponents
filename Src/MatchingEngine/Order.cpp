//
// Created by martin on 14.06.22 г..
//

#include "Order.h"

long Order::getTimestamp() const {
    return m_Timestamp;
}

Side Order::getSide() const {
    return m_Side;
}

oClass Order::getClass() const {
    return m_Class;
}

uint_fast64_t Order::getInitialQuantity() const {
    return m_InitialQuantity;
}

uint_fast64_t Order::getRemainingQuantity() const {
    return m_RemainingQuantity;
}

uint_fast64_t Order::getLimitPrice() const {
    return m_LimitPrice;
}

uint_fast64_t Order::getOrderId() const {
    return m_OrderID;
}

uint_fast64_t Order::getCustomerId() const {
    return m_CustomerID;
}

uint_fast64_t Order::getInstrumentId() const {
    return m_InstrumentID;
}

void Order::setRemainingQuantity(uint_fast64_t mRemainingQuantity) {
    m_RemainingQuantity = mRemainingQuantity;
}

Order::Order(long Timestamp, Side Side, oClass Class, uint_fast64_t Quantity, uint_fast64_t LimitPrice,
             uint_fast64_t OrderID, uint_fast64_t CustomerID, uint_fast64_t InstrumentID) {
    m_Timestamp = Timestamp;
    m_Side = Side;
    m_Class = Class;
    m_InitialQuantity = Quantity;
    m_RemainingQuantity = Quantity;
    m_LimitPrice = LimitPrice;
    m_OrderID = OrderID;
    m_CustomerID = CustomerID;
    m_InstrumentID = InstrumentID;

    PreviousOrder = nullptr;
    NextOrder = nullptr;
    ParentLimit = nullptr;
}

Order *Order::getPreviousOrder() const {
    return PreviousOrder;
}

void Order::setPreviousOrder(Order *previousOrder) {
    PreviousOrder = previousOrder;
}

Order *Order::getNextOrder() const {
    return NextOrder;
}

void Order::setNextOrder(Order *nextOrder) {
    NextOrder = nextOrder;
}

Limit *Order::getParentLimit() const {
    return ParentLimit;
}

void Order::setParentLimit(Limit *parentLimit) {
    ParentLimit = parentLimit;
}

void Order::setMLimitPrice(uint_fast64_t mLimitPrice) {
    if(m_Class == oClass::Limit){
        throw std::runtime_error("Can't change price on limit order");
    }
    m_LimitPrice = mLimitPrice;
}
