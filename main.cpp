#include <iostream>
#include "VariableFloat.h"

int main()
{
    VariableFloat<26, 10> f(-1.001f);
    std::cout << f << std::endl;
    VariableFloat<68, 14> d(-1.001);
    std::cout << d << std::endl;
    return 0;
}