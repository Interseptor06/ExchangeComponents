//
// Created by martin on 18.06.22 г..
//


//
// Created by martin on 20.06.22 г..
//

#pragma once

// Big Thanks to Chronoxor for providing the OrderType code and inspiring some other things

#include <cstdint>

//! Order type
/*!
    Possible values:
    \li <b>Market order</b> - A market order is an order to buy or sell a stock at the best
        available price. Generally, this type of order will be executed immediately. However,
        the price at which a market order will be executed is not guaranteed. It is important
        for investors to remember that the last-traded price is not necessarily the price at
        which a market order will be executed. In fast-moving markets, the price at which a
        market order will execute often deviates from the last-traded price or "real time"
        quote.
    \li <b>Limit order</b> - A limit order is an order to buy or sell a stock at a specific
        price or better. A buy limit order can only be executed at the limit price or lower,
        and a sell limit order can only be executed at the limit price or higher. A limit
        order is not guaranteed to execute. A limit order can only be filled if the stock's
        market price reaches the limit price. While limit orders do not guarantee execution,
        they help ensure that an investor does not pay more than a predetermined price for a
        stock.
    \li <b>Stop order</b> - A stop order, also referred to as a stop-loss order, is an order
        to buy or sell a stock once the price of the stock reaches a specified price, known
        as the stop price. When the stop price is reached, a stop order becomes a market order.
        A buy stop order is entered at a stop price above the current market price. Investors
        generally use a buy stop order to limit a loss or to protect a profit on a stock that
        they have sold short. A sell stop order is entered at a stop price below the current
        market price. Investors generally use a sell stop order to limit a loss or to protect
        a profit on a stock that they own.
    \li <b>Stop-limit order</b> - A stop-limit order is an order to buy or sell a stock that
        combines the features of a stop order and a limit order. Once the stop price is reached,
        a stop-limit order becomes a limit order that will be executed at a specified price (or
        better). The benefit of a stop-limit order is that the investor can control the price at
        which the order can be executed.
    \li <b>Trailing stop order</b> - Not Implemented Yet - A trailing stop order is entered with a
        stop parameter that creates a moving or trailing activation price, hence the name. This parameter
        is entered as a percentage change or actual specific amount of rise (or fall) in the
        security price. Trailing stop sell orders are used to maximize and
        protect profit as a stock's price rises and limit losses when its price falls.
    \li <b>Trailing stop-limit order</b> -Not Implemented Yet - A trailing stop-limit order is similar to a trailing
        stop order. Instead of selling at market price when triggered, the order becomes a limit
        order.
*/

enum class OrderType : uint8_t
{
    MARKET,
    LIMIT,
    STOP,
    STOP_LIMIT
};

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, OrderType type)
{
    switch (type)
    {
        case OrderType::MARKET:
            stream << "MARKET";
            break;
        case OrderType::LIMIT:
            stream << "LIMIT";
            break;
        case OrderType::STOP:
            stream << "STOP";
            break;
        case OrderType::STOP_LIMIT:
            stream << "STOP-LIMIT";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}