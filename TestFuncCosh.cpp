#include "FuncCosh.h"
#include <cassert>
int main() {
    FuncCosh func;
    assert(fabs(func.calculate(0, 1) - 1) < 0.001); // Test for x = 0
    return 0;
}
