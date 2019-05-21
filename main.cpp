#include <iostream>
#include <iomanip>
#include "VariableFloat.h"
#include "util/Timer.h"
#include "test/Test.h"
#include "test/AddTest.h"
#include "test/SubTest.h"
#include "test/MulTest.h"
#include "test/DivTest.h"

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
    srand(time(nullptr));

    //Generate population.
    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);
    //std::vector<int> fractions = {23,52,75,104,150};
    //std::vector<int> exponent = {8,16,24,32};

    //Create floating point numbers from population.
    VariableFloat<23, 8> data1[populationSize];
    AddTest<23,8> add1(data1);
    fillArray(data1, populationSize, randomFloats);
    runTest(add1, data1, populationSize);

    VariableFloat<52, 11> data2[populationSize];
    AddTest<52,11> add2(data2);
    fillArray(data2, populationSize, randomFloats);
    runTest(add2, data2, populationSize);

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

    std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl; */

    VariableFloat<53, 11> g(0.047);
    std::cout << VariableFloat<53, 11>::sqrt(g) << std::endl;

    VariableFloat<23, 8> h(12.678f);
    std::cout << VariableFloat<23, 8>::sqrt(h) << std::endl;

    std::cout << "czas testow (bez after i before): " << std::fixed << result.fullTimeOfTests << std::endl;

    VariableFloat<23, 8> j(false, "03", "9570A4");
    VariableFloat<23, 8> k(false, "02", "C851EC");

    std::cout << j / k << std::endl;
    return 0;
}