//
// Created by martin on 14.06.22 г..
//

#pragma once

enum class Side: bool {
    Buy = true,
    Sell = false
};

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, Side side)
{
    switch (side)
    {
        case Side::Buy:
            stream << "Buy";
            break;
        case Side::Sell:
            stream << "Sell";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}