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
    //0000 0001 0010 0001
    //0000 0010 0100 0010
    std::vector<u_char> b = {0x1, 0x21};
    ByteArray::shiftVectorLeft(b, 1);
    std::cout<<b<<std::endl;
}

void checkIfZeroTest()
{
    std::vector<u_char> buf = {0x0,0x0,0x0};
    std::cout << ByteArray::checkIfZero(buf) << std::endl;
}

int main()
{
    //shiftTest2();
    //return 0;

    VariableFloat<26, 10> f(0.0f);
    std::cout << f << std::endl;
    VariableFloat<23, 8> d(2.5f);
    std::cout << d << std::endl;
    //VariableFloat<23, 8> g(false, "01", "21");
    //VariableFloat<23, 8> h(false, "02", "20");
    //    std::cout << g + h<< std::endl;

    //VariableFloat<23, 8> g(4.5f);
    //VariableFloat<23, 8> h(2.2578125f);

    VariableFloat<23, 8> g(true, "02", "00");
    VariableFloat<23, 8> h(true, "01", "00");


    std::cout << g << std::endl;
    std::cout << h << std::endl;

    std::cout << g - h<< std::endl;


    return 0;
}
