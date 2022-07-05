#include "OrderBook.h"

void OrderBook::load(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: File could not be opened.");
    }


    int lineNumber = 1;
    std::string line;

    while (std::getline(file, line)) {
        try {
            Order entry = Order::tokensToOE(Helpers::tokenize(line, ","));
            entries[entry.timestamp].push_back(entry);
        } catch (const std::exception &e) {
            throw std::runtime_error("Error: CSV contains bad data at: " + std::to_string(lineNumber));
        }
        lineNumber++;
    }

    process();
}

void OrderBook::process() {
    std::set<std::string> uniqueProducts;

    for (const auto &[timestamp, orders]: entries) {
        timestamps.push_back(timestamp);

        if (uniqueProducts.empty())
            for (const auto &order: orders) {
                uniqueProducts.insert((order.product));
            }
    }

    products.assign(uniqueProducts.begin(), uniqueProducts.end());

    for (const auto &product: products) {
        stats[product] = {0, 0, 0, 0};
    }
}

double OrderBook::predictPrice(const std::string &minmax, const std::string &product, const OrderType &orderType) {
    if (minmax == "min") {
        return (orderType == OrderType::ask ? stats[product].minaskEMA : stats[product].minbidEMA);
    } else {
        return (orderType == OrderType::ask ? stats[product].maxaskEMA : stats[product].maxbidEMA);
    }
}

double OrderBook::avgTimesteps(int timeIndex, const std::string &product, const OrderType &orderType, int steps) {
    if (steps > timeIndex) throw std::runtime_error("Number of steps is too large");

    double sum = 0;
    for (int i = timeIndex - 1; i >= timeIndex - steps; i--) {
        sum += Math::mean(getPricesFromOrders(timestamps[i], product, orderType));
    }

    return sum / steps;
}

void OrderBook::updateStats(int timeIndex) {
    const auto &currentTime = timestamps[timeIndex];

    for (auto &[product, stat]: stats) {
        const auto bids = getPricesFromOrders(currentTime, product, OrderType::bid);
        const auto asks = getPricesFromOrders(currentTime, product, OrderType::ask);
        stat.minbidEMA = Math::EMA(timeIndex, Math::min(bids), stat.minbidEMA);
        stat.maxbidEMA = Math::EMA(timeIndex, Math::max(bids), stat.maxbidEMA);
        stat.minaskEMA = Math::EMA(timeIndex, Math::min(asks), stat.minaskEMA);
        stat.maxaskEMA = Math::EMA(timeIndex, Math::max(asks), stat.maxaskEMA);
    }
}

std::string OrderBook::productExists(const std::string &product) {
    if (std::find(products.begin(), products.end(), product) == products.end()) {
        throw std::runtime_error("Error: The product \"" + product + "\" does not exist.");
    }
    return product;
}

std::vector<std::string> OrderBook::getProducts() {
    return products;
}

std::vector<std::string> OrderBook::getTimestamps() {
    return timestamps;
}

std::vector<Order>
OrderBook::getOrders(const std::string &timestamp, const std::string &product, const OrderType &orderType) {
    std::vector<Order> orders;

    for (const auto &order: entries[timestamp]) {
        if (order.product == product && order.orderType == orderType) {
            orders.push_back(order);
        }
    }

    return orders;
}

std::vector<double> OrderBook::getPrices(const std::vector<Order> &orders) {
    std::vector<double> prices;

    for (const auto &order: orders) {
        prices.push_back(order.price);
    }
    return prices;
}

std::vector<double>
OrderBook::getPricesFromOrders(const std::string &timestamp, const std::string &product, const OrderType &orderType) {
    return getPrices(getOrders(timestamp, product, orderType));
}
