#pragma once

#include <string>
#include <vector>
#include <iostream>

enum class OrderType {
    bid,
    ask,
};

class Order {
public:
    /**
     * Constructor that creates an Order
     * @param _timestamp String that represents the timestamp
     * @param _product String that represents a product
     * @param _orderType OrderType which is the type of the order
     * @param _price Price of the order
     * @param _amount Amount of the order
     */
    Order(
            std::string _timestamp,
            std::string _product,
            OrderType _orderType,
            double _price,
            double _amount);

    /**
     * Function to convert a string to an OrderType
     * @param type String containing the name of an order type
    */
    static OrderType stoOT(const std::string &type);

    /**
     * Function to convert a vector of tokens to an Order entry
     * @param tokens vector of strings containing a timestamp, product, order type, price and amount
    */
    static Order tokensToOE(std::vector<std::string> tokens);

    std::string timestamp;
    std::string product;
    OrderType orderType;
    double price;
    double amount;
};