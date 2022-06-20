//
// Created by martin on 15.06.22 г..
//

#include <stdexcept>
#include "OrderTree.h"


OrderTree::OrderTree(Side newSide) : TreeSide(newSide){
    Volume = 0;
    nOrders = 0;
    Depth = 0;

    priceTree = new std::map<uint_fast64_t, Limit*>();
    priceMap = new std::unordered_map<uint_fast64_t, Limit*>();
    orderMap = new std::unordered_map<uint_fast64_t, Order*>();
}


uint_fast64_t OrderTree::getVolume() const {
    return Volume;
}

uint_fast64_t OrderTree::getNOrders() const {
    return nOrders;
}

uint_fast64_t OrderTree::getDepth() const {
    return Depth;
}

Limit *OrderTree::getLimit(uint_fast64_t LimitPrice) {
    auto Temp = priceMap->find(LimitPrice);
    if(Temp != priceMap->end()){
        return Temp->second;
    }
    else {
        return nullptr;
    }
}

Order *OrderTree::getOrder(uint_fast64_t OrderID) {
    auto Temp = orderMap->find(OrderID);
    if(Temp != orderMap->end()){
        return Temp->second;
    }
    else {
        return nullptr;
    }
}

bool OrderTree::limitExists(uint_fast64_t LimitPrice) {
    return priceMap->contains(LimitPrice);
}

bool OrderTree::orderExists(uint_fast64_t OrderID) {
    return orderMap->contains(OrderID);
}

Limit *OrderTree::maxPriceLimit() {
    return priceTree->begin()->second;
}

Limit *OrderTree::minPriceLimit() {
    return priceTree->rbegin()->second;
}

uint_fast64_t OrderTree::maxPrice() {
    return priceTree->begin()->first;
}

uint_fast64_t OrderTree::minPrice() {
    return priceTree->rbegin().operator--()->first;
}

void OrderTree::createPrice(uint_fast64_t newPrice) {
    auto* newLimit = new Limit(newPrice);
    priceTree->emplace(newPrice, newLimit);
    priceMap->emplace(newPrice, newLimit);
    Depth++;
}

void OrderTree::removePrice(uint_fast64_t oldPrice) {
    priceTree->erase(oldPrice);
    priceMap->erase(oldPrice);
    Depth--;
}

void OrderTree::RemoveOrderByID(uint_fast64_t oldOrderID) {
    Order* Temp = orderMap->find(oldOrderID)->second;
    Limit* Parent = Temp->getParentLimit();
    Parent->Remove(*Temp);
    if(Parent->getLength() == 0){
        removePrice(Parent->getLimitPrice());
    }
    orderMap->erase(oldOrderID);

    nOrders--;
    Volume -= Temp->getRemainingQuantity();
}

void OrderTree::InsertOrder(Order &newOrder) {
    if(orderExists(newOrder.getOrderId())){
        throw std::runtime_error("Order Already Exists");
    }
    if(!limitExists(newOrder.getLimitPrice())){
        createPrice(newOrder.getLimitPrice());
    }
    auto* ParentLimit = priceMap->find(newOrder.getLimitPrice())->second;
    ParentLimit->Add(newOrder);
    orderMap->emplace(static_cast<uint_fast64_t>(newOrder.getOrderId()), &newOrder);
    nOrders++;
    Volume += newOrder.getRemainingQuantity();
}

Limit *OrderTree::bestPriceLimit() {
    return TreeSide == Side::Buy ? maxPriceLimit() : minPriceLimit();
}

uint_fast64_t OrderTree::bestPrice() {
    return TreeSide == Side::Buy ? maxPrice() : minPrice();
}

uint_fast64_t OrderTree::getBestVolume(uint_fast64_t Price) {
    uint_fast64_t currentVolume = 0;
    uint_fast64_t currentPrice = bestPrice();

    if(TreeSide == Side::Buy){
        auto TempIter = priceTree->begin();
        while (Price < currentPrice){
            currentVolume += TempIter->second->getVolume();
            TempIter++;
            currentPrice = TempIter->second->getLimitPrice();
        }
    }
    else {
        auto TempIter = ++priceTree->rbegin();
        while (Price > currentPrice){
            currentVolume += TempIter->second->getVolume();
            TempIter++;
            currentPrice = TempIter->second->getLimitPrice();
        }
    }
    return currentVolume;
}
