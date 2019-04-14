#include <iostream>
#include "VariableFloat.h"

int main()
{
    VariableFloat<26, 10> f(-18.47f);
    std::cout << f << std::endl;
    VariableFloat<68, 14> d(19.23);
    std::cout << d << std::endl;
    return 0;
}