//
// Created by martin on 19.06.22 г..
//

#pragma once

#include <cstdint>

// If the actions become more than 256 uint8_t is going to be a big problem
enum class Action : uint8_t {
    Add,
    Cancel
};

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, Action type)
{
    switch (type)
    {
        case Action::Add:
            stream << "Add";
            break;
        case Action::Cancel:
            stream << "ADD";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}
