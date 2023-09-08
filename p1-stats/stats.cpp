// stats.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

std::vector<std::pair<double, int>> summarize(std::vector<double> v) {
    sort(v);
    std::vector<std::pair<double, int>> summary;

    int count = 1;
    size_t size = v.size();
    for (size_t i = 0; i < size; i++) {
        if (v.at(i) == v.at(i - 1)) {
            count++;
        } else {
            summary.emplace_back(v.at(i - 1), count);
            count = 1;
        }
    }
    summary.emplace_back(v.back(), count);

    return summary;
}

int count(std::vector<double> v) {
    return v.size();
}

double sum(std::vector<double> v) {
    double total = 0.0;
    for (size_t i = 0; i < v.size(); i++) {
        total += v.at(i);
    }
    return total;
}

double mean(std::vector<double> v) {
    return sum(v) / static_cast<double>(count(v));
}

double median(std::vector<double> v) {
    size_t n = v.size();
    sort(v);
    if (n % 2 == 0) {
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
    } else {
        return v[n / 2];
    }
}

double mode(std::vector<double> v) {
    sort(v);
    double modeValue = v[0];
    int maxCount = 1;
    int currentCount = 1;

    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == v[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                modeValue = v[i - 1];
            }
            currentCount = 1;
        }
    }

    if (currentCount > maxCount) {
        modeValue = v.back();
    }

    return modeValue;
}

double min(std::vector<double> v) {
    double min = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (min - v[i] > 0.000001) {
            min = v[i];
        }
    }
    return min;
}

double max(std::vector<double> v) {
    double max = v[0];
    for (size_t i = 0; i < v.size(); i++) {
        if (v.at(i) - max > 0.000001) {
            max = v[i];
        }
    }
    return max;
}

double stdev(std::vector<double> v) {
    double meanValue = mean(v);
    double sumSquaredDiffs = 0.0;
    for (double value : v) {
        double diff = value - meanValue;
        sumSquaredDiffs += diff * diff;
    }
    double variance = sumSquaredDiffs / static_cast<double>(v.size() - 1);
    return sqrt(variance);
}

double percentile(std::vector<double> v, double p) {
    sort(v);
    double index = (v.size() - 1) * p;
    int lower = static_cast<int>(floor(index));
    int upper = static_cast<int>(ceil(index));
    double lowerValue = v[lower];
    double upperValue = v[upper];
    return lowerValue + (upperValue - lowerValue) * (index - lower);
}
