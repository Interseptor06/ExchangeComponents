//
// Created by martin on 19.06.22 г..
//

#ifndef ORDERBOOK_OUTBOUNDMESSAGE_H
#define ORDERBOOK_OUTBOUNDMESSAGE_H

#include "InboundMessage.h"
#include <string>
#include <sstream>

class OutboundMessage {
public:
    inline explicit OutboundMessage(InboundMessage &newMsg){
        std::stringstream ss;
        ss << newMsg;
        Msg = new std::string(ss.str());
    }

    [[nodiscard]] inline std::string getMsg() const {
        return *Msg;
    }

private:
    std::string *Msg;
};


#endif //ORDERBOOK_OUTBOUNDMESSAGE_H
