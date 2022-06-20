//
// Created by martin on 19.06.22 г..
//

#ifndef ORDERBOOK_ORDERMATCHINGENGINE_H
#define ORDERBOOK_ORDERMATCHINGENGINE_H

#include <unordered_map>
#include <functional>
#include <atomic>
#include <queue>
#include "../MatchingEngine/OrderBook.h"
#include "InboundMessage.h"
#include "OutboundMessage.h"


/*
 * Most business logic is in the OrderBook class, so that's somewhat offloaded
 * From here on the main goal is going to be to make this module faster, whether that be by making it MultiThreaded
 * or changing the design.
 */
class OrderMatchingEngine {
public:
    OrderMatchingEngine();
    uint_fast64_t AddNewOrderBook(); // Returns new InstrumentID
    void RemoveOldOrderBook(uint_fast64_t oldInstrumentID);
    OutboundMessage ProcessInboundMessage(InboundMessage &newMsg);
    std::list<uint_fast64_t> getSymbols;
private:
    std::unordered_map<uint_fast64_t, OrderBook*>* Symbols; // <InstrumentID, OrderBook>
    std::atomic_int_fast64_t* LastInstrumentID;
    std::atomic_int_fast64_t* LastOrderID;
};


#endif //ORDERBOOK_ORDERMATCHINGENGINE_H
