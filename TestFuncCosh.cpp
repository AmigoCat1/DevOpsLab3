#include "FuncCosh.h"
#include <cassert>
#include <cmath>

int main() {
    FuncCosh function;

    assert(std::fabs(function.calculate(0, 1) - 1) < 0.001);  // cosh(0) should be 1
    assert(std::fabs(function.calculate(1, 10) - std::cosh(1.0)) < 0.001); // Compare with std::cosh
    assert(std::fabs(function.calculate(-1, 10) - std::cosh(-1.0)) < 0.001); // cosh(-1) = cosh(1)

    return 0;
}

