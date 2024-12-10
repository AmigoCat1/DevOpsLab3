#include <iostream>
#include "FuncCosh.h"

int CreateHTTPserver();

int main() {
	FuncCosh func;
        double x;
        int n;
	// Input x and terms
	std::cout << "Enter the value of x: ";
	std::cin >> x;
	std::cout << "Enter the number of terms: ";
	std::cin >> terms;
	// Output result
	std::cout << "ch(" << x << ") = " << func.calculate(x, terms) << std::endl;
	std::cout << "Start HTTP server" << std::endl;
    	CreateHTTPserver();
	return 0;
}
