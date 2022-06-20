//
// Created by martin on 19.06.22 г..
//

#include "OrderMatchingEngine.h"

OrderMatchingEngine::OrderMatchingEngine() {
    Symbols = new std::unordered_map<uint_fast64_t, OrderBook*>;
    LastInstrumentID = new std::atomic_int_fast64_t(0);
    LastOrderID = new std::atomic_int_fast64_t(0);
}
uint_fast64_t OrderMatchingEngine::AddNewOrderBook() {
    Symbols->emplace(LastInstrumentID->operator++(), new OrderBook());
    return LastInstrumentID->load();
}

void OrderMatchingEngine::RemoveOldOrderBook(uint_fast64_t oldInstrumentID) {
    Symbols->erase(oldInstrumentID);
}

OutboundMessage OrderMatchingEngine::ProcessInboundMessage(InboundMessage &newMsg) {
    if(newMsg.m_Action == Action::Add){
        newMsg.m_newOrderID = LastOrderID->operator++();
    }
    auto ParentSymbol = Symbols->find(newMsg.m_InstrumentID);
    if(ParentSymbol != Symbols->end()){
        auto* ParentBook = ParentSymbol->second;
        ParentBook->ProcessInboundMsg(newMsg);
        return *(new OutboundMessage(newMsg));
    } else{
        throw std::runtime_error("Book Doesn't Exist");
    }
}
