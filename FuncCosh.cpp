#include "FuncCosh.h"
#include <cmath>
#include <stdexcept>

unsigned long long FuncCosh::calculateFactorial(int n) {
    if (n > 20) { // Factorial overflow limit
        throw std::runtime_error("Factorial overflow detected");
    }

    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }

    return result;
}

double FuncCosh::calculate(double x, int terms) {
    double sum = 1.0;  // Start from the first term cosh(0) = 1
    for (int n = 1; n < terms; ++n) {
        sum += std::pow(x, 2 * n) / calculateFactorial(2 * n);
    }
    return sum;
}

