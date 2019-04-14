#include <iostream>
#include "Float.h"

int main()
{
    auto * f = new Float<23, 8>(-1.001f);
    f->printContainers(std::cout);
    delete f;
    auto * d = new Float<52, 11>(-1.001);
    d->printContainers(std::cout);
    delete d;
    return 0;
}