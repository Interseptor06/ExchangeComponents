//
// Created by martin on 15.06.22 г..
//

#include <numeric>
#include "OrderBook.h"

OrderBook::OrderBook() {
    Bids = new OrderTree(Side::Buy);
    Asks = new OrderTree(Side::Sell);

    Trades = new std::vector<TradeReport*>();
}

uint_fast64_t OrderBook::getBestBid() {
    return Bids->maxPrice();
}

uint_fast64_t OrderBook::getWorstBid() {
    return Bids->minPrice();
}

uint_fast64_t OrderBook::getBestAsk() {
    return Asks->minPrice();
}

uint_fast64_t OrderBook::getWorstAsk() {
    return Asks->maxPrice();
}

uint_fast64_t OrderBook::getSpread() {
    return getBestAsk() - getBestBid();
}

uint_fast64_t OrderBook::getMid() {
    return std::midpoint(getBestBid(), getBestAsk());
}

bool OrderBook::bidsAndAsksExist() {
    return ((Bids->getNOrders() > 0) && (Asks->getNOrders() > 0));
}

uint_fast64_t OrderBook::getVolumeOnSide(Side _side) {
    if(_side == Side::Buy){
        return Bids->getVolume();
    }
    else{
        return Asks->getVolume();
    }
}

void OrderBook::DeleteOrder(uint_fast64_t OldOrderID) {
    if (Bids->orderExists(OldOrderID)) {
        Bids->RemoveOrderByID(OldOrderID);
    } else if (Asks->orderExists(OldOrderID)) {
        Asks->RemoveOrderByID(OldOrderID);
    }
}

// Tries to match and if unsuccessful - adds remains to OrderBook
void OrderBook::AddLimitOrder(Order &newOrder) {
    auto QuantityRemaining = newOrder.getInitialQuantity();
    auto OrderPrice = newOrder.getLimitPrice();
    uint_fast64_t CurrentPrice = newOrder.getSide() == Side::Buy ? Asks->bestPrice()
                                                                 : Bids->bestPrice(); // Best Price on the other side of the book
    auto *TradeTape = new std::vector<Trade>;

    if (newOrder.getSide() == Side::Buy) {

        if (OrderPrice >= CurrentPrice) { // OrderPrice "goes into" the other side of the book
            auto *CurrentBestLimit = Asks->bestPriceLimit();
            CurrentPrice = Asks->bestPrice();

            while (OrderPrice >= CurrentPrice && Asks->getNOrders() > 0 && QuantityRemaining > 0) {
                auto TmpPair = CurrentBestLimit->getFirstVolume(QuantityRemaining);

                if (TmpPair.first >= QuantityRemaining) {
                    for (const auto &x: TmpPair.second) {
                        TradeTape->push_back(*(new Trade(CurrentNanoTime(),
                                                         x.getLimitPrice(),
                                                         x.getRemainingQuantity(),
                                                         newOrder.getCustomerId(),
                                                         x.getCustomerId(),
                                                         newOrder.getOrderId(),
                                                         x.getOrderId(),
                                                         newOrder.getInstrumentId())));
                    }
                    QuantityRemaining = 0;
                } else {
                    for (const auto &x: TmpPair.second) {
                        TradeTape->push_back(*(new Trade(CurrentNanoTime(),
                                                         x.getLimitPrice(),
                                                         x.getRemainingQuantity(),
                                                         newOrder.getCustomerId(),
                                                         x.getCustomerId(),
                                                         newOrder.getOrderId(),
                                                         x.getOrderId(),
                                                         newOrder.getInstrumentId())));
                        QuantityRemaining -= x.getRemainingQuantity();
                    }
                    CurrentPrice = Asks->bestPrice();
                }
            }
            if(QuantityRemaining > 0){
                Bids->InsertOrder(newOrder);
            }
        }
        else{
            Bids->InsertOrder(newOrder);
        }
    } else {

        if (OrderPrice <= CurrentPrice) { // OrderPrice "goes into" the other side of the book
            auto *CurrentBestLimit = Bids->bestPriceLimit();
            CurrentPrice = Bids->bestPrice();

            while (OrderPrice <= CurrentPrice && Bids->getNOrders() > 0 && QuantityRemaining > 0) {
                auto TmpPair = CurrentBestLimit->getFirstVolume(QuantityRemaining);

                if (TmpPair.first >= QuantityRemaining) {
                    for (const auto &x: TmpPair.second) {
                        TradeTape->push_back(*(new Trade(CurrentNanoTime(),
                                                         x.getLimitPrice(),
                                                         x.getRemainingQuantity(),
                                                         newOrder.getCustomerId(),
                                                         x.getCustomerId(),
                                                         newOrder.getOrderId(),
                                                         x.getOrderId(),
                                                         newOrder.getInstrumentId())));
                    }
                    QuantityRemaining = 0;
                }
                else {
                    for (const auto &x: TmpPair.second) {
                        TradeTape->push_back(*(new Trade(CurrentNanoTime(),
                                                         x.getLimitPrice(),
                                                         x.getRemainingQuantity(),
                                                         newOrder.getCustomerId(),
                                                         x.getCustomerId(),
                                                         newOrder.getOrderId(),
                                                         x.getOrderId(),
                                                         newOrder.getInstrumentId())));
                        QuantityRemaining -= x.getRemainingQuantity();
                    }
                    CurrentPrice = Asks->bestPrice();
                }
            }
            newOrder.setRemainingQuantity(QuantityRemaining);
            if(QuantityRemaining > 0){
                Asks->InsertOrder(newOrder);
            }
        }
        else {
            Asks->InsertOrder(newOrder);
        }
    }
    Trades->push_back(new TradeReport(TradeTape));
}

void OrderBook::AddMarketOrder(Order &newOrder){
    if(newOrder.getSide() == Side::Buy) {
        newOrder.setMLimitPrice(Bids->bestPrice());
    } else {
        newOrder.setMLimitPrice(Asks->bestPrice());
    }
    AddLimitOrder(newOrder);
}

void OrderBook::AddOrder(Order &newOrder) {
    if(newOrder.getClass() == OrderType::LIMIT){
        AddLimitOrder(newOrder);
    }
    else if(newOrder.getClass() == OrderType::MARKET){
        AddMarketOrder(newOrder);
    }
}

void OrderBook::ModifyOrder(uint_fast64_t id, uint_fast64_t new_price, uint_fast64_t new_quantity) {
    throw std::runtime_error("Unimplemented");
}

void OrderBook::ModifyQuantity(uint_fast64_t id, uint_fast64_t new_quantity) {
    auto* Order = FindOrder(id);
    auto PriceDiff = std::max(Order->getInitialQuantity(), new_quantity) - std::min(Order->getInitialQuantity(), new_quantity);
    bool InitialLess = Order->getInitialQuantity() < new_quantity;
    if(InitialLess){
        Order->setRemainingQuantity(Order->getRemainingQuantity() + PriceDiff);
    }
    else{
        Order->setRemainingQuantity(Order->getRemainingQuantity() - PriceDiff);
    }
    auto* ParentLimit = Order->getParentLimit();
    ParentLimit->MoveToTail(*Order);
}

Order *OrderBook::FindOrder(uint_fast64_t id) {
    Order *MyOrder;
    if(Bids->orderExists(id)){
        MyOrder = Bids->getOrder(id);
    }
    else if(Asks->orderExists(id)){
        MyOrder = Asks->getOrder(id);
    }
    else{
        return nullptr;
    }
    return MyOrder;
}