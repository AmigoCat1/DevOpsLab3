// Use library
#include <gtest/gtest.h>
#include "FuncCosh.h"
#include <cmath>

// Test to verify the result for x = 0
TEST(CoshFunctionTest, ZeroInput) {
    FuncCosh func;
    EXPECT_NEAR(func.calculate(0.0, 3), 1.0, 1e-6); // cosh(0) = 1
}

// Test to verify the result for x = 1 (positive value)
TEST(CoshFunctionTest, PositiveInput) {
    FuncCosh func;
    double x = 1.0;
    EXPECT_NEAR(func.calculate(x, 10), std::cosh(x), 1e-6); // Compare with the standard library cosh
}

// Test to verify the result for x = -1 (negative value)
TEST(CoshFunctionTest, NegativeInput) {
    FuncCosh func;
    double x = -1.0;
    EXPECT_NEAR(func.calculate(x, 10), std::cosh(x), 1e-6); // cosh is symmetric, cosh(-x) = cosh(x)
}

// Test for x = 2 with a limited number of terms in the series
TEST(CoshFunctionTest, LimitedTerms) {
    FuncCosh func;
    double x = 2.0;
    EXPECT_NEAR(func.calculate(x, 5), std::cosh(x), 0.1); // Less precision due to limited terms
}

// Test for large values of x
TEST(CoshFunctionTest, LargeInput) {
    FuncCosh func;
    double x = 10.0;
    EXPECT_NEAR(func.calculate(x, 20), std::cosh(x), 1e-6); // Higher precision for large x with more terms
}

