// stats.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

std::vector<std::pair<double, int>> summarize(std::vector<double> v) {
    std::vector<std::pair<double, int>> result;
    sort(v);

    double current_value = v[0];
    int current_frequency = 1;

    for (size_t i = 1; i < v.size(); i++) {
        if (std::abs(v[i] - current_value) < 0.0000001) {
            current_frequency++;
        } else {
            result.push_back({current_value, current_frequency});
            current_value = v.at(i);
            current_frequency = 1;
        }
    }

    // Push the last element
    result.push_back({current_value, current_frequency});


    return result;
}

int count(std::vector<double> v) {
    return static_cast<int>(v.size());
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

    for (size_t i = 1; i < v.size(); i++) {
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
    sort(v);
    return v[0];
}

double max(std::vector<double> v) {
    sort(v);
    return v[v.size() - 1];
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
    double rank = p * static_cast<double>(count(v) - 1) + 1;
    double floor = static_cast<int>(rank);
    double ceil = rank - floor;
    if (ceil == 0.0) {
        return v.at(floor - 1);
    } else { 
        double percentile = v.at(floor - 1) + ceil * (v.at(floor) - v.at(floor - 1));
        return percentile;
    }
}
