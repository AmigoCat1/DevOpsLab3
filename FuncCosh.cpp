#include "FuncCosh.h"
#include <cmath>
#include <stdexcept>

unsigned long long FuncCosh::factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double FuncCosh::calculate(double x, int terms) {
    double sum = 0.0;
    for (int n = 0; n < terms; ++n) {
        sum += std::pow(x, 2 * n) / factorial(2 * n);
    }
    return sum;
}
