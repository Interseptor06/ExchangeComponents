//
// Created by martin on 20.06.22 г..
//

#ifndef ORDERBOOK_ERRORS_H
#define ORDERBOOK_ERRORS_H

#include <cstdint>

enum class ErrorCode : uint8_t
{
    OK,
    SYMBOL_DUPLICATE,
    SYMBOL_NOT_FOUND,
    ORDER_BOOK_DUPLICATE,
    ORDER_BOOK_NOT_FOUND,
    ORDER_DUPLICATE,
    ORDER_NOT_FOUND,
    ORDER_ID_INVALID,
    ORDER_TYPE_INVALID,
    ORDER_PARAMETER_INVALID,
    ORDER_QUANTITY_INVALID
};

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, ErrorCode error)
{
    switch (error)
    {
        case ErrorCode::OK:
            stream << "OK";
            break;
        case ErrorCode::SYMBOL_DUPLICATE:
            stream << "SYMBOL_DUPLICATE";
            break;
        case ErrorCode::SYMBOL_NOT_FOUND:
            stream << "SYMBOL_NOT_FOUND";
            break;
        case ErrorCode::ORDER_BOOK_DUPLICATE:
            stream << "ORDER_BOOK_DUPLICATE";
            break;
        case ErrorCode::ORDER_BOOK_NOT_FOUND:
            stream << "ORDER_BOOK_NOT_FOUND";
            break;
        case ErrorCode::ORDER_DUPLICATE:
            stream << "ORDER_DUPLICATE";
            break;
        case ErrorCode::ORDER_NOT_FOUND:
            stream << "ORDER_NOT_FOUND";
            break;
        case ErrorCode::ORDER_ID_INVALID:
            stream << "ORDER_ID_INVALID";
            break;
        case ErrorCode::ORDER_TYPE_INVALID:
            stream << "ORDER_TYPE_INVALID";
            break;
        case ErrorCode::ORDER_PARAMETER_INVALID:
            stream << "ORDER_PARAMETER_INVALID";
            break;
        case ErrorCode::ORDER_QUANTITY_INVALID:
            stream << "ORDER_QUANTITY_INVALID";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}
#endif //ORDERBOOK_ERRORS_H
