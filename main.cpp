#include <iostream>
#include <iomanip>
#include "VariableFloat.h"
#include "util/Timer.h"
#include "test/Test.h"
#include "test/AddTest.h"
#include "test/SubTest.h"
#include "test/MulTest.h"
#include "test/DivTest.h"

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


template<int fraction, int exponent>
Test::TestResult runTest(UnitTimeTest& testObj, VariableFloat<fraction, exponent> data[], int size){

    Test t;

    //each test takes two variable float
    Test::TestResult result = t.createTest(testObj, size/2);

    result.exponent = exponent;
    result.fraction = fraction;

    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"sredni czas wykonania           : "<<std::fixed<<result.avgTimePerTest<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    result.toCsv(std::cerr);

    return result;
}

int main()
{
    srand(time(NULL));


    /*VariableFloat<23, 8> data[] = {
            VariableFloat<23, 8>(0.1254f),
            VariableFloat<23, 8>(0.7503f),
            VariableFloat<23, 8>(1.5f),
            VariableFloat<23, 8>(2.5f),
            VariableFloat<23, 8>(1.125f),
            VariableFloat<23, 8>(2.750f)
    };*/

    //generate population
    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);
    //std::vector<int> fractions = {23,52,75,104,150};
    //std::vector<int> exponent = {8,16,24,32};

    //create floats from population
    VariableFloat<23, 8> data1[populationSize];
    AddTest<23,8> add1(data1);
    fillArray(data1, populationSize, randomFloats);
    runTest(add1, data1, populationSize);

    //create floats from population
    VariableFloat<52, 11> data2[populationSize];
    AddTest<52,11> add2(data2);
    fillArray(data2, populationSize, randomFloats);
    runTest(add2, data2, populationSize);

    //create floats from population
    VariableFloat<104, 18> data3[populationSize];
    AddTest<104,18> add3(data3);
    fillArray(data3, populationSize, randomFloats);
    runTest(add3, data3, populationSize);

    /*SubTest<23,8> sub(data);
    result = t.createTest(sub, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    MulTest<23,8> mul(data);
    result = t.createTest(mul, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    DivTest<23,8> dev(data);
    result = t.createTest(dev, 3);
    std::cout<<"ilosc testow                    : "<<std::fixed<<result.testCount<<std::endl;
    std::cout<<"czas calosciowy testow          : "<<std::fixed<<result.fullTime<<std::endl;
    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    VariableFloat<23, 8> g(false, "03", "9570A4");
    VariableFloat<23, 8> h(false, "02", "C851EC");

    std::cout << g / h << std::endl;*/
    return 0;
}
