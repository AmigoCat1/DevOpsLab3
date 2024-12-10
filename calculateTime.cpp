#include "calculateTime.h"
#include "FuncCosh.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

int calculateTime() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<double> aValues;
    FuncCosh calc;
    std::random_device rd;
    std::mt19937 mtre(rd());
    std::uniform_real_distribution<double> distr(-10.0, 10.0); // Range of values for hyperbolic cosine

    // Generate 1,000,000 random values and calculate their function
    for (int i = 0; i < 2000000; i++) {
        double randomValue = distr(mtre);
        double calculatedValue = calc.calculate(randomValue, 10); // Using 10 terms for the Taylor series
        aValues.push_back(calculatedValue);
    }

    // Sort the array 500 times
    for (int i = 0; i < 500; i++) {
        std::sort(aValues.begin(), aValues.end());
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    return int_ms.count();
}

