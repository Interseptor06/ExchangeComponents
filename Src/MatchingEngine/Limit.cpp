//
// Created by martin on 15.06.22 г..
//

#include <stdexcept>
#include "Limit.h"

// Tail.getNext = null always
// Head.getPrev = null
void Limit::Add(Order &newOrder) {
    //newOrder.getParentLimit() == nullptr && newOrder.getPreviousOrder() == nullptr && newOrder.getNextOrder() == nullptr
    if(newOrder.getParentLimit() == nullptr && newOrder.getPreviousOrder() == nullptr && newOrder.getNextOrder() == nullptr){
        newOrder.setParentLimit(this);
        if(Length == 0 && HeadOrder == nullptr){
            newOrder.setNextOrder(nullptr);
            newOrder.setPreviousOrder(nullptr);
            HeadOrder = &newOrder;
            TailOrder = &newOrder;
        }
        else{
            newOrder.setPreviousOrder(nullptr);
            newOrder.setNextOrder(TailOrder);
            TailOrder->setPreviousOrder(&newOrder);
            TailOrder = &newOrder;
        }
        Length++;
        Volume += newOrder.getRemainingQuantity();
        OrderIds->insert(newOrder.getOrderId());
    }
    else{
        throw std::runtime_error("Order Already Belongs To a Limit");
    }
}

void Limit::Remove(Order &oldOrder) {
    if(oldOrder.getLimitPrice() != LimitPrice || !OrderIds->contains(oldOrder.getOrderId()) || this->Length == 0){
        throw std::runtime_error("Order isn't in Limit");
    }
    else{
        OrderIds->erase(oldOrder.getOrderId());
        Order* tempNextOrder = oldOrder.getNextOrder();
        Order* tempPrevOrder = oldOrder.getPreviousOrder();
        if ((tempNextOrder != nullptr) && (tempPrevOrder != nullptr)) {
            tempNextOrder->setPreviousOrder(tempPrevOrder);
            tempPrevOrder->setNextOrder(tempNextOrder);
        }
        else if (tempNextOrder != nullptr) {
            tempNextOrder->setPreviousOrder(nullptr);
            this->HeadOrder = tempNextOrder;
        }
        else if (tempPrevOrder != nullptr) {
            tempPrevOrder->setNextOrder(nullptr);
            this->TailOrder = tempPrevOrder;
        }
        this->Volume -= oldOrder.getRemainingQuantity();
        this->Length -= 1;
    }
    delete &oldOrder;
}


void Limit::RemoveWithoutDelete(Order &oldOrder) {
    if (oldOrder.getLimitPrice() != LimitPrice || !OrderIds->contains(oldOrder.getOrderId()) || this->Length == 0) {
        throw std::runtime_error("Order isn't in Limit");
    } else {
        OrderIds->erase(oldOrder.getOrderId());
        Order *tempNextOrder = oldOrder.getNextOrder();
        Order *tempPrevOrder = oldOrder.getPreviousOrder();
        if ((tempNextOrder != nullptr) && (tempPrevOrder != nullptr)) {
            tempNextOrder->setPreviousOrder(tempPrevOrder);
            tempPrevOrder->setNextOrder(tempNextOrder);
        } else if (tempNextOrder != nullptr) {
            tempNextOrder->setPreviousOrder(nullptr);
            this->HeadOrder = tempNextOrder;
        } else if (tempPrevOrder != nullptr) {
            tempPrevOrder->setNextOrder(nullptr);
            this->TailOrder = tempPrevOrder;
        }
        oldOrder.setPreviousOrder(nullptr);
        oldOrder.setNextOrder(nullptr);
        oldOrder.setParentLimit(nullptr);

        this->Volume -= oldOrder.getRemainingQuantity();
        this->Length -= 1;
    }
}

// Gets first N shares and removes necessary Orders
std::pair<uint_fast64_t, std::vector<Order>> Limit::getFirstVolume(unsigned long expectedVolume) {
    auto* FirstOrders = new std::vector<Order>();
    unsigned long resultingVolume = this->Volume >= expectedVolume ? expectedVolume : this->Volume;
    // Num of shares currently in the list
    uint_fast64_t inVolume = 0;
    if (Length > 0) // This ensures that Head isn't a null reference
    {
        while (inVolume < resultingVolume)
        {
            if (HeadOrder->getRemainingQuantity() <= resultingVolume)
            {
                FirstOrders->push_back(*HeadOrder);
                Order *TempOrder = this->HeadOrder;
                this->RemoveWithoutDelete(*TempOrder);
                inVolume += TempOrder->getRemainingQuantity();
                Length--;
                // As of this moment tempOrder.RemainingQuantity = tempOrder.InitialQuantity
                Volume -= TempOrder->getRemainingQuantity();
            }
            else if (HeadOrder->getRemainingQuantity() > resultingVolume)
            {
                auto* TempOrder = new Order(HeadOrder->getTimestamp(),
                                            HeadOrder->getSide(),
                                            HeadOrder->getClass(),
                                            resultingVolume - HeadOrder->getRemainingQuantity(),
                                            HeadOrder->getLimitPrice(),
                                            HeadOrder->getOrderId(),
                                            HeadOrder->getCustomerId(),
                                            HeadOrder->getInstrumentId());
                // As of this moment tempOrder.RemainingQuantity = tempOrder.InitialQuantity
                HeadOrder->setRemainingQuantity(TempOrder->getRemainingQuantity());
                FirstOrders->push_back(*TempOrder);
                inVolume += TempOrder->getRemainingQuantity();
                Volume -= TempOrder->getRemainingQuantity();
            }
        }
    }
    return *(new std::pair<uint_fast64_t, std::vector<Order>>(inVolume, *FirstOrders));
}

std::pair<uint_fast64_t, std::vector<Order>> Limit::FirstOrders(unsigned long expectedLength) {
    auto* FirstOrders = new std::vector<Order>();
    unsigned long resultingSize = this->Length >= expectedLength ? expectedLength : this->Length;
    // Num of shares currently in the list
    uint_fast64_t inSize = 0;

    Order* TempOrder = HeadOrder;
    while(inSize < resultingSize){
        FirstOrders->push_back(*TempOrder);
        TempOrder = TempOrder->getPreviousOrder();
        inSize++;
    }
    return *(new std::pair<uint_fast64_t, std::vector<Order>>(inSize, *FirstOrders));
}

unsigned long Limit::getVolume() const {
    return Volume;
}

unsigned long Limit::getLength() const {
    return Length;
}

Limit::Limit(uint_fast64_t limitPrice) : LimitPrice(limitPrice) {
    HeadOrder = nullptr;
    TailOrder = nullptr;

    Volume = 0;
    Length = 0;

    OrderIds = new std::unordered_set<uint_fast64_t>;
}

uint_fast64_t Limit::getLimitPrice() const {
    return LimitPrice;
}

bool operator<(const Limit &lhs, const Limit &rhs) {
    return lhs.LimitPrice < rhs.LimitPrice;
}

bool operator>(const Limit &lhs, const Limit &rhs) {
    return rhs < lhs;
}

bool operator<=(const Limit &lhs, const Limit &rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Limit &lhs, const Limit &rhs) {
    return !(lhs < rhs);
}

bool operator==(const Limit &lhs, const Limit &rhs) {
    return lhs.LimitPrice == rhs.LimitPrice;
}

bool operator!=(const Limit &lhs, const Limit &rhs) {
    return !(rhs == lhs);
}

void Limit::MoveToTail(Order &oldOrder) {
    if (oldOrder.getPreviousOrder() != nullptr) {
        oldOrder.getPreviousOrder()->setNextOrder(oldOrder.getNextOrder());
    } else {
        // Update head order
        this->HeadOrder = oldOrder.getNextOrder();
    }
    oldOrder.getNextOrder()->setPreviousOrder(oldOrder.getPreviousOrder());
    // Set the previous tail's next order to this order
    this->TailOrder->setNextOrder(&oldOrder);
    oldOrder.setPreviousOrder(this->TailOrder);
    this->TailOrder = &oldOrder;
    oldOrder.setNextOrder(nullptr);
}
