#include <iostream>
#include "func.h"

int main() {
	double x;
	int terms;
	// Input x and terms
	std::cout << "Enter the value of x: ";
	std::cin >> x;
	std::cout << "Enter the number of terms: ";
	std::cin >> terms;
	// Output result
	double result = calculateCosh(x, terms);
	std::cout << "ch(" << x << ") = " << result << std::endl;

	return 0;
}
