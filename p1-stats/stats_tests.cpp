/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_count();
void test_sum_small_data_set();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();
// Add prototypes for you test functions here.

int main() {
    test_count();
    test_sum_small_data_set();
    test_mean();
    test_median();
    test_mode();
    test_min();
    test_max();
    test_stdev();
    test_percentile();
    // Call your test functions here

    return 0;
}

void test_count() {
    cout << "test_count" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(count(data) == 10);

    cout << "PASS!" << endl;
}

void test_sum_small_data_set() {
    cout << "test_sum_small_data_set" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);

    assert(sum(data) == 6);

    cout << "PASS!" << endl;
}


void test_mean() {
    cout << "test_mean" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(mean(data) == 3);

    cout << "PASS!" << endl;
}

void test_median() {
    cout << "test_median" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(median(data) == 3);

    cout << "PASS!" << endl;
}

void test_mode() {
    cout << "test_mode" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(2);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(mode(data) == 2);

    cout << "PASS!" << endl;
}

void test_min() {
    cout << "test_min" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(min(data) == 1);

    cout << "PASS!" << endl;
}

void test_max() {
    cout << "test_max" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(max(data) == 6);

    cout << "PASS!" << endl;
}

void test_stdev() {
    cout << "test_stdev" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(stdev(data) - 1.6329932 < 0.00000001);

    cout << "PASS!" << endl;
}

void test_percentile() {
    cout << "test_percentile" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(2);
    data.push_back(3);
    data.push_back(3);
    data.push_back(1);

    assert(percentile(data, 0.25) == 2);
    assert(percentile(data, 0.50) == 3);
    assert(percentile(data, 0.75) == 3.75);
    assert(percentile(data, 1.0) == 6);

    cout << "PASS!" << endl;
}

// Add the test function implementations here.