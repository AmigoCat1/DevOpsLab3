#include "func.h"
#include <cmath>
#include <iostream>

// Function for calculating factorial 
unsigned long long factorial(int n) {
        unsigned long long result = 1;
        for (int i = 2; i <= n; ++i) {
                result *= i;
        }
        return result;
}

// Function for calculating hyperbolic cosine
double calculateCosh(double x, int terms) {
	double sum = 0.0;
	for (int n = 0; n < terms; ++n) {
		sum += pow(x, 2 * n) / factorial(2 * n);
	}
	return sum;
}
