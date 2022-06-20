//
// Created by martin on 20.06.22 г..
//

#pragma once

#include <cstdint>

//! Order Time in Force
/*!
    Possible values:
    \li <b>Good-Till-Cancelled (GTC)</b> - A GTC order is an order to buy or sell a stock that
        lasts until the order is completed or cancelled.
    \li <b>Immediate-Or-Cancel (IOC)</b> - An IOC order is an order to buy or sell a stock that
        must be executed immediately. Any portion of the order that cannot be filled immediately
        will be cancelled.
    \li <b>Fill-Or-Kill (FOK)</b> - An FOK order is an order to buy or sell a stock that must
        be executed immediately in its entirety; otherwise, the entire order will be cancelled
        (i.e., no partial execution of the order is allowed).
    \li <b>All-Or-None (AON)</b> - An All-Or-None (AON) order is an order to buy or sell a stock
        that must be executed in its entirety, or not executed at all. AON orders that cannot be
        executed immediately remain active until they are executed or cancelled.
*/
enum class OrderTimeInForce : uint8_t
{
    GTC,    //!< Good-Till-Cancelled
    IOC,    //!< Immediate-Or-Cancel
    FOK,    //!< Fill-Or-Kill
    AON     //!< All-Or-None - Basically PartialFill = False
};

template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, OrderTimeInForce tif);