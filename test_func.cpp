// Use library
#include <gtest/gtest.h>
#include <cmath>
#include "func.h"

// Test to verify the result for x = 0
TEST(ChFunctionTest, ZeroInput) {
    EXPECT_NEAR(calculateCosh(0.0, 3), 1.0, 1e-6);
}

// Test to verify the result for x = 1 (positive value)
TEST(ChFunctionTest, PositiveInput) {
    double x = 1.0;
    EXPECT_NEAR(calculateCosh(x, 10), std::cosh(x), 1e-6);
}

// Test to verify the result for x = -1 (negative value)
TEST(ChFunctionTest, NegativeInput) {
    double x = -1.0;
    EXPECT_NEAR(calculateCosh(x, 10), std::cosh(x), 1e-6);
}


