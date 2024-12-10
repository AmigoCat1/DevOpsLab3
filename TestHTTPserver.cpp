#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
#include "FuncCosh.h"

// Test: Check for x = 0
void test_cosh_zero() {
    FuncCosh calc;
    assert(fabs(calc.calculate(0.0, 5) - 1.0) < 0.001);
}

// Test: Check for x = 1
void test_cosh_one() {
    FuncCosh calc;
    double expected = std::cosh(1.0); // Using the library function for comparison
    assert(fabs(calc.calculate(1.0, 10) - expected) < 0.001);
}

// Test: Check for x = -1
void test_cosh_negative_one() {
    FuncCosh calc;
    double expected = std::cosh(-1.0); // cosh(-x) = cosh(x)
    assert(fabs(calc.calculate(-1.0, 10) - expected) < 0.001);
}

// Test: Calculation time
void test_calculation_time() {
    FuncCosh calc;
    auto start = std::chrono::high_resolution_clock::now();

    // Perform calculations for a large number of terms
    calc.calculate(10.0, 1000);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "Calculation time: " << duration << " milliseconds" << std::endl;
    assert(duration >= 5000 && duration <= 20000); // Expected calculation time between 5 and 20 seconds
}

int main() {
    test_cosh_zero();
    test_cosh_one();
    test_cosh_negative_one();
    test_calculation_time();
    std::cout << "All unit tests complete" << std::endl;
    return 0;
}

