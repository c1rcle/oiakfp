#include <iostream>
#include <iomanip>
#include "VariableFloat.h"
#include "Timer.h"
#include "Test.h"
#include "AddTest.h"
#include "SubTest.h"
#include "MulTest.h"
#include "DevTest.h"

void divideTest()
{
    std::vector<u_char> first = {0xA4, 0x57};
    std::vector<u_char> second = {0xC0, 0x12};
    ByteArray::divideBytes(first, second, 20);
    std::cout << first << std::endl;
}

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
    ByteArray::addBytesEqualSize(buf, buf2);
    std::cout<<buf<<std::endl;
}

int main()
{
    VariableFloat<23, 8> data []= {VariableFloat<23, 8>(1.0f),
                                               VariableFloat<23, 8>(2.0f),
                                               VariableFloat<23, 8>(1.5f),
                                               VariableFloat<23, 8>(2.5f),
                                               VariableFloat<23, 8>(1.125f),
                                               VariableFloat<23, 8>(2.750f)
                                              };

    Test t;
    AddTest<23,8> add(data);
    Test::TestResult result = t.createTest(add, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    SubTest<23,8> sub(data);
    result = t.createTest(sub, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    MulTest<23,8> mul(data);
    result = t.createTest(mul, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    DevTest<23,8> dev(data);
    result = t.createTest(dev, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    //std::cout<<(data[1]+data[0]).toBinary()<<std::endl;

    //divideTest();

    /*
    std::vector<u_char> vec = {0xFF, 0x0F, 0xF0, 0x00};
    std::cout<<ByteArray::toBinaryString(vec, 10)<<std::endl;
*/
    /*VariableFloat<52, 11> first(1.0f);
    VariableFloat<52, 11> second(2.0f);

    std::cout << "   " << first << std::endl;
    std::cout << "+  " << second << std::endl;
    std::cout << "=  "  << first + second << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;*/
/*
    //VariableFloat<23, 8> g(false, "01", "21");
    //VariableFloat<23, 8> h(false, "02", "20");
    //    std::cout << g + h<< std::endl;

    //VariableFloat<23, 8> g(4.5f);
    //VariableFloat<23, 8> h(2.2578125f);

    //VariableFloat<23, 8> g(2.53f);
    //VariableFloat<23, 8> h(4.67f);
    VariableFloat<23, 8> g(true, "06", "F0");   //1.0 -> 10 = 2
    VariableFloat<23, 8> h(false, "04", "00"); //1.1 -> 110 = 6


    std::cout << "   " << g << std::endl;
    std::cout << "*  " << h << std::endl;
    std::cout << "=  " << g + h << std::endl;
    std::cout << std::endl;

    std::cout << "std:    " << g << std::endl;
    std::cout << "binary: " << g.toBinary() <<std::endl; */
    VariableFloat<23, 8> g(12.456f);
    VariableFloat<23, 8> h(2.5f);

    std::cout << g / h << std::endl;
    return 0;
}
