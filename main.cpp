#include <iostream>
#include <iomanip>
#include "VariableFloat.h"
#include "Timer.h"

void shiftTest()
{
    std::vector<u_char> bytes = {0xFF,0xFF,0xFF,0xFF};
    for(unsigned int i = 0; i <= bytes.size() * 8; ++i)
    {
        std::vector<u_char> buf = bytes;
        ByteArray::shiftVectorRight(buf, i);
    }
}
void checkIfZeroTest()
{
    std::vector<u_char> buf = {0x0,0x0,0x0};
    std::cout << ByteArray::checkIfZero(buf) << std::endl;
}

int main()
{
    VariableFloat<26, 10> f(0.0f);
    std::cout << f << std::endl;
    VariableFloat<68, 14> d(2.0f);
    std::cout << d << std::endl;
    return 0;
}
