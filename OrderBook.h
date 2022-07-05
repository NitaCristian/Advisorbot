#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "Helpers.h"
#include "Order.h"
#include "Math.h"

class Stat {
public:
    double minbidEMA;
    double maxbidEMA;
    double minaskEMA;
    double maxaskEMA;
};

class OrderBook {
public:
    /**
     * Function which loads data from a file
     * @param file File from which to load data
     */
    void load(const std::string &filename);

    /**
     * Function to process loaded data
     */
    void process();

    /**
     * Function which returns a statistic based on given parameters
     * @param minmax String which can be "min" or "max"
     * @param product String of product
     * @param type OrderType of order
     * @return value of a statistic which is an EMA value
     */
    double predictPrice(const std::string &minmax, const std::string &product, const OrderType &orderType);

    /**
     * Function which calculates the average over given number of timesteps
     * @param timeIndex Index of the current time
     * @param product String of product
     * @param type OrderType of order
     * @param steps Number of steps
     * @return average over given number of steps
     */
    double avgTimesteps(int timeIndex, const std::string &product, const OrderType &orderType, int steps);

    /**
     * Function which checks if a given string is a valid product
     * @param product String of product
     * @return the product if it's valid
     * @throw runtime_error if the product is not valid
     */
    std::string productExists(const std::string &product);

    /**
     * Function which updates statistics for each product with values at given timeIndex
     * @param timeIndex Index of the timestamp
     */
    void updateStats(int timeIndex);

    /**
     * Funtion to get all orders that match the specified parameters
     * @param timestamp The current timestamp
     * @param product The product of the orders
     * @param orderType The order type of the orders
     * @return Vector with orders
     */
    std::vector<Order> getOrders(const std::string &timestamp, const std::string &product, const OrderType &orderType);

    /**
     * Function to get all prices from a vector of orders
     * @param orders Orders from which to extract prices
     * @return Vector of values
     */
    static std::vector<double> getPrices(const std::vector<Order> &orders);

    /**
     * Combined function of getOrders and getPrices for simplyfication
     * @param timestamp The current timestamp
     * @param product The product of the orders
     * @param orderType The order type of the orders
     * @return Vector of values
     */
    std::vector<double>
    getPricesFromOrders(const std::string &timestamp, const std::string &product, const OrderType &orderType);

    /**
     * Function that returns all the products
     * @return vector of all products
     */
    std::vector<std::string> getProducts();

    /**
     * Function that returns all timestamps
     * @return vector of all timestamps
     */
    std::vector<std::string> getTimestamps();

private:
    // Map which assigns each product a statistic
    std::map<std::string, Stat> stats;

    // Vector of all products
    std::vector<std::string> products;

    // Vector of all timestamps
    std::vector<std::string> timestamps;

    // Map which assigns each timestamp a vector of orders
    std::map<std::string, std::vector<Order>> entries;
};