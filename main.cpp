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
        ByteArray::shiftVectorLeft(buf, i);
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

void multiplyTest(){
    std::vector<u_char> buf = {0xff,0xff,0xff,0xff};
    std::vector<u_char> buf2 = {0xff, 0xff};
    ByteArray::multiplyBytes(buf, buf2);
    std::cout<<buf<<std::endl;
}

void addTest(){
    std::vector<u_char> buf = {0x0, 0x0, 0xfe, 0xff, 0xff, 0x1};
    std::vector<u_char> buf2 = {0x0, 0xfe, 0xff, 0xff, 0x1, 0x0};
    ByteArray::addBytesEqSize(buf, buf2);
    std::cout<<buf<<std::endl;
}

int main()
{
    std::vector<u_char> a = {0,0,0,0};
    std::cout<<a<<std::endl;
    ByteArray::setBit(a, 28, 1);

    std::cout<<a<<", "<<ByteArray::findOldestOnePostition(a)<<std::endl;
    //return 0;


    VariableFloat<52, 11> s(0.0);
    //std::cin>>s;
    //std::cout<<"entered value: "<<s<<std::endl;


    VariableFloat<52, 11> first(2.2578125);
    VariableFloat<52, 11> second(4.5);

    std::cout << "   " << first << std::endl;
    std::cout << "*  " << second << std::endl;
    std::cout << "   "  << first + second << std::endl;
    std::cout << std::endl;

    //multiplyTest();
    //return 0;
    VariableFloat<23, 8> f(1/3.0);
    //std::cout << f << std::endl;
    //return 0;
    VariableFloat<23, 8> d(2.5f);
    //std::cout << d << std::endl;
    //VariableFloat<23, 8> g(false, "01", "21");
    //VariableFloat<23, 8> h(false, "02", "20");
    //    std::cout << g + h<< std::endl;

    //VariableFloat<23, 8> g(4.5f);
    //VariableFloat<23, 8> h(2.2578125f);

//    VariableFloat<23, 8> g(true, "01", "10");
//    VariableFloat<23, 8> h(true, "02", "10");
    VariableFloat<23, 8> g(true, "01", "F0");   //1.0 -> 10 = 2
    VariableFloat<23, 8> h(true, "02", "F0"); //1.1 -> 110 = 6


    std::cout << "   " << g << std::endl;
    std::cout << "*  " << h << std::endl;
    std::cout << "   " << g * h << std::endl;
    std::cout << std::endl;
    return 0;
}
