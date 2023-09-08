// main.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <iostream>

using namespace std;

int main() {
    string filename;
    string column_name;

    cout << "enter a filename" << endl;
    cin >> filename;
    cout << "enter a column name" << endl;
    cin >> column_name;
    vector<double> v = extract_column(filename, column_name);

    //Summary (value: frequency)
    // 6: 1
    // 7: 1
    // 8: 1
    // 9: 1
    // 10: 1
    // count = 5
    // sum = 40
    // mean = 8
    // stdev = 1.58114
    // median = 8
    // mode = 6
    // min = 6
    // max = 10
    // 0th percentile = 6
    // 25th percentile = 7
    // 50th percentile = 8
    // 75th percentile = 9
    // 100th percentile = 10
    vector<pair<double, int>> answer = summarize(v);
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].first << ": " << answer[i].second << endl;
    }

    cout << "count = " << count(v) << endl;
    cout << "sum = " << sum(v) << endl;
    cout << "mean = " << mean(v) << endl;
    cout << "stdev = " << stdev(v) << endl;
    cout << "median = " << median(v) << endl;
    cout << "mode = " << mode(v) << endl;
    cout << "min = " << min(v) << endl;
    cout << "max = " << max(v) << endl;
    

    return 0;
}