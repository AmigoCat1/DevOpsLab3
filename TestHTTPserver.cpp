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
    assert(fabs(calc.calculate(0.0, 5) - 1.0) < 0.001);
}

void test_cosh_one() {
    FuncCosh calc;
    assert(fabs(calc.calculate(1.0, 10) - cosh(1.0)) < 0.001); // Compare with std::cosh
}

void test_calculation_time() {
    int iMS = calculateTime();
    std::cout << "Calculation and sorting time: " << iMS << " milliseconds" << std::endl;
    assert(iMS >= 5000 && iMS <= 20000); // Condition calculation time is within 5 to 20 sec
}

int main() {
    test_cosh_zero();
    test_cosh_one();
    test_calculation_time();
    std::cout << "All tests completed" << std::endl;
    return 0;
}
