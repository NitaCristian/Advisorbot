#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

class Math {
public:
    /**
        * Statistical function which calculates an Exponential Moving Average
        * @param t Time at which the EMA is calculated
        * @param value Value at time t
        * @param oldEMA Previous value of the EMA
        * @return Value of EMA at time t
        */
    static double EMA(int t, double value, double oldEMA);

    /**
     * Statistical function which calculates the mean of a vector of values
     * @param values Vector of values
     * @return mean of the vector
     */
    static double mean(const std::vector<double> &values);

    /**
     * Statistical function which calculates the median of a vector of values
     * @param values Vector of values
     * @return element in the middle
     */
    static double median(std::vector<double> values);

    /**
     * Statistical function which returns the minimum value in a vector of values
     * @param values Vector of values
     * @return Minimum value
     */
    static double min(const std::vector<double> &values);

    /**
     * Statistical function which returns the maximum value in a vector of values
     * @param values Vector of values
     * @return Maximum value
     */
    static double max(const std::vector<double> &values);

    /**
    * Statistical function which calculates the bid-ask spread
    * @param asks Vector of ask prices
    * @param bids Vector of bid prices
    * @return Spread between bids and asks
    */
    static double bidAskSpread(const std::vector<double> &asks, const std::vector<double> &bids);

};