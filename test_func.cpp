#include "func.h"
#include <gtest/gtest.h>
#include <cmath>

// Test to verify the result for x = 0
TEST(CoshFunctionTest, ZeroInput) {
    EXPECT_NEAR(ch(0.0), 1.0, 1e-6);
}

// Test to verify the result for x = 1
TEST(CoshFunctionTest, PositiveInput) {
    double x = 1.0;
    EXPECT_NEAR(ch(x), std::cosh(x), 1e-6);
}

// Test to verify the result for x = -1
TEST(CoshFunctionTest, NegativeInput) {
    double x = -1.0;
    EXPECT_NEAR(ch(x), std::cosh(x), 1e-6);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

