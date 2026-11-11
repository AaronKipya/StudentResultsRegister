
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <string>

#include "Sorting.h"

using namespace std;
using namespace std::chrono;

int main() {
    const vector<int> sizes = {
        1000, 2000, 4000, 8000,
        16000, 32000, 64000
    };

    const int runs = 3;

    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 1000000);

    ofstream csv("benchmark_results.csv");

    if (!csv.is_open()) {
        cerr << "Cannot create benchmark_results.csv\n";
        return 1;
    }

    csv << "Size,Insertion_ms,QuickSort_ms,"
           "Insertion_Ratio,QuickSort_Ratio\n";

    cout << "STUDENT RESULTS REGISTER - BENCHMARK\n";
    cout << "====================================\n";
    cout << "Each algorithm runs 3 times per size.\n\n";

    cout << left << setw(10) << "Size"
         << setw(18) << "Insertion (ms)"
         << setw(18) << "Quicksort (ms)"
         << setw(16) << "Insertion Ratio"
         << "Quick Ratio\n";

    cout << string(78, '-') << "\n";

    double previousInsertion = 0;
    double previousQuick = 0;

    auto ascending = [](int a, int b) {
        return a < b;
    };

    for (int n : sizes) {
        double insertionTotal = 0;
        double quickTotal = 0;

        for (int run = 0; run < runs; ++run) {
            vector<int> original(n);

            for (int& value : original) {
                value = dist(rng);
            }

            vector<int> insertionData = original;
            vector<int> quickData = original;

            auto start = steady_clock::now();

            insertionSort(
                insertionData.data(),
                insertionData.size(),
                ascending
            );

            auto end = steady_clock::now();

            insertionTotal +=
                duration<double, milli>(end - start).count();

            start = steady_clock::now();

            quickSort(
                quickData.data(),
                quickData.size(),
                ascending
            );

            end = steady_clock::now();

            quickTotal +=
                duration<double, milli>(end - start).count();

            // Verify correctness outside timed sections
            if (!is_sorted(insertionData.begin(),
                           insertionData.end()) ||
                !is_sorted(quickData.begin(),
                           quickData.end()) ||
                insertionData != quickData) {
                cerr << "Sorting verification failed!\n";
                return 1;
            }
        }

        double insertionAvg = insertionTotal / runs;
        double quickAvg = quickTotal / runs;

        double insertionRatio =
            previousInsertion > 0
                ? insertionAvg / previousInsertion
                : 0;

        double quickRatio =
            previousQuick > 0
                ? quickAvg / previousQuick
                : 0;

        cout << fixed << setprecision(3)
             << left << setw(10) << n
             << setw(18) << insertionAvg
             << setw(18) << quickAvg
             << setw(16) << insertionRatio
             << quickRatio << "\n";

        csv << fixed << setprecision(6)
            << n << ","
            << insertionAvg << ","
            << quickAvg << ","
            << insertionRatio << ","
            << quickRatio << "\n";

        previousInsertion = insertionAvg;
        previousQuick = quickAvg;
    }

    csv.close();

    cout << "\nBenchmark completed successfully!\n";
    cout << "Results saved to benchmark_results.csv\n";

    return 0;
}
