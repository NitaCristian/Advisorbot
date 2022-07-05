#include "Order.h"

Order::Order(std::string _timestamp, std::string _product, OrderType _orderType, double _price, double _amount) :
        timestamp(_timestamp), product(_product), orderType(_orderType), price(_price), amount(_amount) {}

OrderType Order::stoOT(const std::string &type) {
    if (type == "ask")
        return OrderType::ask;
    if (type == "bid")
        return OrderType::bid;

    throw std::invalid_argument("Error: The order type \"" + type + "\" does not exist.");
}

Order Order::tokensToOE(std::vector<std::string> tokens) {
    OrderType orderType;
    double price;
    double amount;

    try {
        orderType = stoOT(tokens[2]);
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: Could not convert tokens to double.");
    }

    return {tokens[0], tokens[1], orderType, price, amount};
}
