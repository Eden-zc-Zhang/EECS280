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

// Add prototypes for you test functions here.

int main() {
    test_count();
    test_sum_small_data_set();
    test_mean();
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


// Add the test function implementations here.