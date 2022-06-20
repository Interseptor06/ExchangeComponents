//
// Created by martin on 15.06.22 г..
//

#pragma once

#include "Order.h"
#include <vector>
#include <unordered_set>
#include <cstdint>

class Order;

class Limit {
public:
    Limit(uint_fast64_t limitPrice); // Doesn't need to be explicit
    Limit(const Limit&) noexcept = default;
    Limit(Limit&&) noexcept = default;
    ~Limit() noexcept = default;

    Limit& operator=(const Limit&) noexcept = default;
    Limit& operator=(Limit&&) noexcept = default;

    void Add(Order &newOrder);
    void Remove(Order &oldOrder);
    void RemoveWithoutDelete(Order &oldOrder);

    void MoveToTail(Order &oldOrder);

    std::pair<uint_fast64_t, std::vector<Order>> getFirstVolume(unsigned long expectedVolume);
    std::pair<uint_fast64_t, std::vector<Order>> FirstOrders(unsigned long n = 5);

    [[nodiscard]] unsigned long getVolume() const;
    [[nodiscard]] unsigned long getLength() const;

    [[nodiscard]] uint_fast64_t getLimitPrice() const;

    friend bool operator<(const Limit &lhs, const Limit &rhs);

    friend bool operator>(const Limit &lhs, const Limit &rhs);

    friend bool operator<=(const Limit &lhs, const Limit &rhs);

    friend bool operator>=(const Limit &lhs, const Limit &rhs);

    friend bool operator==(const Limit &lhs, const Limit &rhs);

    friend bool operator!=(const Limit &lhs, const Limit &rhs);

private:
    Order* HeadOrder;
    Order* TailOrder;

    uint_fast64_t LimitPrice;

    unsigned long Volume; // Number of outstanding shares
    unsigned long Length; // Number of Orders

    std::unordered_set<uint_fast64_t>* OrderIds;

};