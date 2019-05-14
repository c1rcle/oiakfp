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
        std::cout<<buf<<std::endl;
    }
}

void shiftTest2()
{
    std::vector<u_char> b = {0x1, 0x21};
    ByteArray::shiftVectorRight(b, 1);
    std::cout<<b<<std::endl;
}

void checkIfZeroTest()
{
    std::vector<u_char> buf = {0x0,0x0,0x0};
    std::cout << ByteArray::checkIfZero(buf) << std::endl;
}

int main()
{
    //shiftTest();
    //return 0;
    VariableFloat<52, 11> g(2.2578125);
    VariableFloat<52, 11> h(4.5);
    std::cout << g + h << std::endl;
    return 0;
}
