#include <iostream>
#include "FuncCosh.h"




int CreateHTTPserver();

int main() {

    signal(SIGCHLD, sigchldHandler);	
    signal(SIGINT, sigintHandler);
    FuncCosh func;
    double x;
    int n;

    std::cout << "Enter x and n: ";
    std::cin >> x >> n;

    std::cout << "Result function FuncCosh: " << func.calculate(x, n) << std::endl;

    std::cout << "Start HTTP server" << std::endl;
    CreateHTTPserver();

    return 0;
}
