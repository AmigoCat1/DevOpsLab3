#include <iostream>
#include <cmath>
#include <cassert>
#include "FuncCosh.h"
#include "calculateTime.h"

void verifyCoshAtZero() {
    FuncCosh calculator;
    assert(std::fabs(calculator.calculate(0.0, 5) - 1.0) < 0.001);
}

void verifyCoshAtPositiveOne() {
    FuncCosh calculator;
    assert(std::fabs(calculator.calculate(1.0, 10) - std::cosh(1.0)) < 0.001); //Compare with std::cosh
}

void verifyCoshAtNegativeOne() {
    FuncCosh calculator;
    assert(std::fabs(calculator.calculate(-1.0, 10) - std::cosh(-1.0)) < 0.001);
}

void checkCalculationTime() {
    int elapsedTime = calculateTime();
    std::cout << "Computation and sort time for task: " << elapsedTime << " ms" << std::endl;
    assert(elapsedTime >= 5000 && elapsedTime <= 30000); // Condition calculation time is within 5 to 30 sec
}

int main() {
    verifyCoshAtZero();
    verifyCoshAtPositiveOne();
    verifyCoshAtNegativeOne();
    checkCalculationTime();
    std::cout << "Tests completed successfully." << std::endl;
    return 0;
}

