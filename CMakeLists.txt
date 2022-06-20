cmake_minimum_required(VERSION 3.21)
project(OrderBook)

set(CMAKE_CXX_STANDARD 20)

add_executable(OrderBook main.cpp Src/MatchingEngine/Order.cpp Src/MatchingEngine/Order.h Src/MatchingEngine/OrderSide.h Src/MatchingEngine/Limit.cpp Src/MatchingEngine/Limit.h Src/MatchingEngine/OrderTree.cpp Src/MatchingEngine/OrderTree.h Src/MatchingEngine/OrderBook.cpp Src/MatchingEngine/OrderBook.h Src/MatchingEngine/OrderType.h Src/MatchingEngine/Trade.h Src/MatchingEngine/utils.h Src/WorkInProgress/OrderMatchingEngine.cpp Src/WorkInProgress/OrderMatchingEngine.h Src/WorkInProgress/InboundMessage.h Src/WorkInProgress/Action.h Src/WorkInProgress/OutboundMessage.h Src/MatchingEngine/Errors.h Src/MatchingEngine/OrderTimeInForce.h Src/MessageQueue/Message.cpp Src/MessageQueue/Message.h Src/MessageQueue/Queue.cpp Src/MessageQueue/Queue.h)
