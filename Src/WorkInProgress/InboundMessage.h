//
// Created by martin on 19.06.22 г..
//

#ifndef ORDERBOOK_INBOUNDMESSAGE_H
#define ORDERBOOK_INBOUNDMESSAGE_H

#include <ostream>
#include "Action.h"
#include "../MatchingEngine/OrderSide.h"
#include "../MatchingEngine/OrderType.h"

struct InboundMessage {
    inline friend std::ostream &operator<<(std::ostream &os, const InboundMessage &message) {
        std::string TmpSide = message.m_Side == Side::Buy ? "Bid" : "Ask";
        std::string TmpOClass = message.m_Class == oClass::Limit ? "Limit" : "Market";

        if(message.m_Action == Action::Add){
            os << "m_Action: " <<  "Add" << " m_Timestamp: " <<message.m_Timestamp
            << " m_Side: " << TmpSide<< " m_Class: " << TmpOClass
            << " m_Quantity: " << message.m_Quantity
            << " m_LimitPrice: " << message.m_LimitPrice
            << " m_newOrderID: " << message.m_newOrderID
            << " m_CustomerID: " << message.m_CustomerID << " m_InstrumentID: " << message.m_InstrumentID;
        }
        else{
            os << "m_Action: " <<  "Cancel"  << " m_oldOrderID: " << message.m_oldOrderID;
        }

        return os;
    }

    Action m_Action; // Add or Cancel
    long m_Timestamp;
    Side m_Side;
    oClass m_Class; // Market Or Limit
    uint_fast64_t  m_Quantity;
    uint_fast64_t m_LimitPrice; // in cents
    uint_fast64_t m_oldOrderID; // In case of cancel, this is what we use
    uint_fast64_t m_newOrderID; // New OrderID Generated By Matching Engine
    uint_fast64_t m_CustomerID;
    uint_fast64_t m_InstrumentID;
};

#endif //ORDERBOOK_INBOUNDMESSAGE_H
