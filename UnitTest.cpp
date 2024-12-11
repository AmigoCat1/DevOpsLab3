#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>
#include "FuncCosh.h"
#include "calculateTime.h"

void test_cosh_zero() {
    FuncCosh calc;
    double result = calc.calculate(0.0, 5);
    std::cout << "cosh(0) calculated value: " << result << std::endl;
    assert(fabs(result - 1.0) < 0.001);
}

void test_cosh_one() {
    FuncCosh calc;
    double result = calc.calculate(1.0, 10);
    std::cout << "cosh(1) calculated value: " << result << std::endl;
    assert(fabs(result - cosh(1.0)) < 0.001); // Compare with std::cosh
}

void test_calculation_time() {
    int iMS = calculateTime();
    std::cout << "Calculation and sorting time: " << iMS << " milliseconds" << std::endl;
    assert(iMS >= 5000 && iMS <= 20000); 
}

int main() {
    test_cosh_zero();
    test_cosh_one();
    test_calculation_time();
    std::cout << "All tests complete" << std::endl;
    return 0;
}
