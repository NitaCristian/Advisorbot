#include "Math.h"

double Math::EMA(int t, double value, double oldEMA) {
    if (t == 0) return value;

    const double alpha = 0.125;
    return alpha * value + (1 - alpha) * oldEMA;
}

double Math::mean(const std::vector<double> &values) {
    return std::accumulate(values.begin(), values.end(), 0.0) / (double) values.size();
}

double Math::median(std::vector<double> values) {
    std::sort(values.begin(), values.end());

    auto index = values.size() / 2;
    if (index % 2 == 0) {
        return (values[index - 1] + values[index]) / 2;
    }
    return values[index];
}

double Math::min(const std::vector<double> &values) {
    return *std::min_element(values.begin(), values.end());
}

double Math::max(const std::vector<double> &values) {
    return *std::max_element(values.begin(), values.end());
}

double Math::bidAskSpread(const std::vector<double> &asks, const std::vector<double> &bids) {
    return min(asks) - max(bids);
}