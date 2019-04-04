#include <iostream>
#include "Float.h"

void test()
{
    auto * string = new u_char[2];
    auto * string2 = new u_char[2];

    string[0] = 10;
    string[1] = 11;

    string2[0] = 3;
    string2[1] = 5;
    addBytes(string, string2, 4);
    printf("%d %d", string2[0], string2[1]);
}

int main()
{
    auto * f = new Float<23, 8>(-1.001f);
    f->printContainers(std::cout);
    auto * d = new Float<52, 11>(-1.001);
    d->printContainers(std::cout);
    return 0;
}