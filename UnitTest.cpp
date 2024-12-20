#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
#include "FuncCosh.h"
#include "calculateTime.h"

void testCoshAtZero() {
    FuncCosh calculator;
    double result = calculator.calculate(0.0, 5);
    std::cout << "Cosh(0) computed value: " << result << std::endl;
    assert(std::fabs(result - 1.0) < 0.001); // Expect cosh(0) = 1
}

void testCoshAtPositiveValue() {
    FuncCosh calculator;
    double result = calculator.calculate(1.0, 10);
    std::cout << "Cosh(1) computed value: " << result << std::endl;
    assert(std::fabs(result - std::cosh(1.0)) < 0.001); // Compare with std::cosh
}

void testCoshAtNegativeValue() {
    FuncCosh calculator;
    double result = calculator.calculate(-1.0, 10);  
    std::cout << "Cosh(-1) computed value: " << result << std::endl;
    assert(std::fabs(result - std::cosh(-1.0)) < 0.001); // Compare with cosh(-1)
}

void testExecutionTime() {
    int elapsedTime = calculateTime();
    std::cout << "Total computation time: " << elapsedTime << " ms" << std::endl;
    assert(elapsedTime >= 5000 && elapsedTime <= 30000); // Expected time range
}

int main() {
    testCoshAtZero();
    testCoshAtPositiveValue();
    testCoshAtNegativeValue();
    testExecutionTime();
    std::cout << "All tests have finished." << std::endl;
    return 0;
}

