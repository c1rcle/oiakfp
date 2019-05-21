#include <iostream>
#include <iomanip>
#include "VariableFloat.h"
#include "util/Timer.h"
#include "test/Test.h"
#include "test/AddTest.h"
#include "test/SubTest.h"
#include "test/MulTest.h"
#include "test/DivTest.h"
#include "test/SqrtTest.h"

#define addUnitTest(a,b)  {VariableFloat<a, b> data[populationSize]; \
                          AddTest<a,b> add(data); \
                          fillArray(data, populationSize, randomFloats); \
                          runTest(add, data, populationSize); }

#define subUnitTest(a,b)  {VariableFloat<a, b> data[populationSize]; \
                          SubTest<a,b> add(data); \
                          fillArray(data, populationSize, randomFloats); \
                          runTest(add, data, populationSize); }

#define divUnitTest(a,b)  {VariableFloat<a, b> data[populationSize]; \
                          DivTest<a,b> add(data); \
                          fillArray(data, populationSize, randomFloats); \
                          runTest(add, data, populationSize); }

#define mulUnitTest(a,b)  {VariableFloat<a, b> data[populationSize]; \
                          MulTest<a,b> add(data); \
                          fillArray(data, populationSize, randomFloats); \
                          runTest(add, data, populationSize); }

#define sqrtUnitTest(a,b)  {VariableFloat<a, b> data[populationSize]; \
                           SqrtTest<a,b> add(data); \
                           fillArray(data, populationSize, randomFloats); \
                           runTest(add, data, populationSize); }


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

void sqrtTestCombo(){

    //generate population
    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);


    std::cerr<<"Pierwiastek"<<std::endl;
    std::cerr<<"Zmienna mantsa staly wykladnik"<<std::endl;

    sqrtUnitTest(20,8);
    sqrtUnitTest(30,8);
    sqrtUnitTest(40,8);
    sqrtUnitTest(50,8);
    sqrtUnitTest(60,8);
    sqrtUnitTest(70,8);
    sqrtUnitTest(80,8);
    sqrtUnitTest(90,8);
    sqrtUnitTest(100,8);
    sqrtUnitTest(110,8);
    sqrtUnitTest(120,8);
    sqrtUnitTest(130,8);
    sqrtUnitTest(140,8);
    sqrtUnitTest(150,8);
    sqrtUnitTest(160,8);
    sqrtUnitTest(170,8);
    sqrtUnitTest(180,8);
    sqrtUnitTest(190,8);
    sqrtUnitTest(200,8);
    sqrtUnitTest(210,8);
    sqrtUnitTest(220,8);
    sqrtUnitTest(230,8);
    sqrtUnitTest(240,8);
    sqrtUnitTest(250,8);
    sqrtUnitTest(260,8);
    sqrtUnitTest(270,8);
    sqrtUnitTest(280,8);
    sqrtUnitTest(290,8);
    sqrtUnitTest(300,8);
    sqrtUnitTest(310,8);
    sqrtUnitTest(320,8);
    sqrtUnitTest(330,8);
    sqrtUnitTest(340,8);
    sqrtUnitTest(350,8);
    sqrtUnitTest(360,8);
    sqrtUnitTest(370,8);
    sqrtUnitTest(380,8);
    sqrtUnitTest(390,8);
    sqrtUnitTest(400,8);
    sqrtUnitTest(410,8);
    sqrtUnitTest(420,8);
    sqrtUnitTest(430,8);
    sqrtUnitTest(440,8);
    sqrtUnitTest(450,8);
    sqrtUnitTest(460,8);
    sqrtUnitTest(470,8);
    sqrtUnitTest(480,8);
    sqrtUnitTest(490,8);

    std::cerr<<"Zmienny wykladnik stala mantysa"<<std::endl;
    populationSize = 10;

    sqrtUnitTest(200,8);
    sqrtUnitTest(200,16);
    sqrtUnitTest(200,24);
    sqrtUnitTest(200,32);
    sqrtUnitTest(200,40);
    sqrtUnitTest(200,48);
    sqrtUnitTest(200,56);
    sqrtUnitTest(200,64);
}

void addTestCombo(){

    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);

    std::cerr<<"Dodawanie"<<std::endl;
    std::cerr<<"Zmienna mantsa staly wykladnik"<<std::endl;

    addUnitTest(20,8);
    addUnitTest(30,8);
    addUnitTest(40,8);
    addUnitTest(50,8);
    addUnitTest(60,8);
    addUnitTest(70,8);
    addUnitTest(80,8);
    addUnitTest(90,8);
    addUnitTest(100,8);
    addUnitTest(110,8);
    addUnitTest(120,8);
    addUnitTest(130,8);
    addUnitTest(140,8);
    addUnitTest(150,8);
    addUnitTest(160,8);
    addUnitTest(170,8);
    addUnitTest(180,8);
    addUnitTest(190,8);
    addUnitTest(200,8);
    addUnitTest(210,8);
    addUnitTest(220,8);
    addUnitTest(230,8);
    addUnitTest(240,8);
    addUnitTest(250,8);
    addUnitTest(260,8);
    addUnitTest(270,8);
    addUnitTest(280,8);
    addUnitTest(290,8);
    addUnitTest(300,8);
    addUnitTest(310,8);
    addUnitTest(320,8);
    addUnitTest(330,8);
    addUnitTest(340,8);
    addUnitTest(350,8);
    addUnitTest(360,8);
    addUnitTest(370,8);
    addUnitTest(380,8);
    addUnitTest(390,8);
    addUnitTest(400,8);
    addUnitTest(410,8);
    addUnitTest(420,8);
    addUnitTest(430,8);
    addUnitTest(440,8);
    addUnitTest(450,8);
    addUnitTest(460,8);
    addUnitTest(470,8);
    addUnitTest(480,8);
    addUnitTest(490,8);

    std::cerr<<"Zmienny wykladnik stala mantysa"<<std::endl;
    populationSize = 10;

    addUnitTest(200,8);
    addUnitTest(200,16);
    addUnitTest(200,24);
    addUnitTest(200,32);
    addUnitTest(200,40);
    addUnitTest(200,48);
    addUnitTest(200,56);
    addUnitTest(200,64);
    /*addUnitTest(200,72);
    addUnitTest(200,80);
    addUnitTest(200,96);
    addUnitTest(200,104);
    addUnitTest(200,112);
    addUnitTest(200,120);
    addUnitTest(200,128);
    addUnitTest(200,136);
    addUnitTest(200,144);
    addUnitTest(200,152);
    addUnitTest(200,160);*/

    /*addUnitTest(200,168);
    addUnitTest(200,176);
    addUnitTest(200,184);
    addUnitTest(200,192);
    addUnitTest(200,200);
    addUnitTest(200,208);
    addUnitTest(200,216);
    addUnitTest(200,224);
    addUnitTest(200,232);
    addUnitTest(200,240);
    addUnitTest(200,248);
    addUnitTest(200,256);
    addUnitTest(200,264);
    addUnitTest(200,272);
    addUnitTest(200,280);
    addUnitTest(200,288);
    addUnitTest(200,296);
    addUnitTest(200,304);
    addUnitTest(200,312);
    addUnitTest(200,320);*/
}

void subTestCombo(){

    //generate population
    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);

    std::cerr<<"Odejmowanie"<<std::endl;
    std::cerr<<"Zmienna mantsa staly wykladnik"<<std::endl;

    subUnitTest(20,8);
    subUnitTest(30,8);
    subUnitTest(40,8);
    subUnitTest(50,8);
    subUnitTest(60,8);
    subUnitTest(70,8);
    subUnitTest(80,8);
    subUnitTest(90,8);
    subUnitTest(100,8);
    subUnitTest(110,8);
    subUnitTest(120,8);
    subUnitTest(130,8);
    subUnitTest(140,8);
    subUnitTest(150,8);
    subUnitTest(160,8);
    subUnitTest(170,8);
    subUnitTest(180,8);
    subUnitTest(190,8);
    subUnitTest(200,8);
    subUnitTest(210,8);
    subUnitTest(220,8);
    subUnitTest(230,8);
    subUnitTest(240,8);
    subUnitTest(250,8);
    subUnitTest(260,8);
    subUnitTest(270,8);
    subUnitTest(280,8);
    subUnitTest(290,8);
    subUnitTest(300,8);
    subUnitTest(310,8);
    subUnitTest(320,8);
    subUnitTest(330,8);
    subUnitTest(340,8);
    subUnitTest(350,8);
    subUnitTest(360,8);
    subUnitTest(370,8);
    subUnitTest(380,8);
    subUnitTest(390,8);
    subUnitTest(400,8);
    subUnitTest(410,8);
    subUnitTest(420,8);
    subUnitTest(430,8);
    subUnitTest(440,8);
    subUnitTest(450,8);
    subUnitTest(460,8);
    subUnitTest(470,8);
    subUnitTest(480,8);
    subUnitTest(490,8);


    std::cerr<<"Zmienny wykladnik stala mantysa"<<std::endl;
    populationSize = 10;

    subUnitTest(200,8);
    subUnitTest(200,16);
    subUnitTest(200,24);
    subUnitTest(200,32);
    subUnitTest(200,40);
    subUnitTest(200,48);
    subUnitTest(200,56);
    subUnitTest(200,64);
}

void mulTestCombo(){

    //generate population
    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);

    std::cerr<<"Mnozenie"<<std::endl;
    std::cerr<<"Zmienna mantsa staly wykladnik"<<std::endl;

    mulUnitTest(20,8);
    mulUnitTest(30,8);
    mulUnitTest(40,8);
    mulUnitTest(50,8);
    mulUnitTest(60,8);
    mulUnitTest(70,8);
    mulUnitTest(80,8);
    mulUnitTest(90,8);
    mulUnitTest(100,8);
    mulUnitTest(110,8);
    mulUnitTest(120,8);
    mulUnitTest(130,8);
    mulUnitTest(140,8);
    mulUnitTest(150,8);
    mulUnitTest(160,8);
    mulUnitTest(170,8);
    mulUnitTest(180,8);
    mulUnitTest(190,8);
    mulUnitTest(200,8);
    mulUnitTest(210,8);
    mulUnitTest(220,8);
    mulUnitTest(230,8);
    mulUnitTest(240,8);
    mulUnitTest(250,8);
    mulUnitTest(260,8);
    mulUnitTest(270,8);
    mulUnitTest(280,8);
    mulUnitTest(290,8);
    mulUnitTest(300,8);
    mulUnitTest(310,8);
    mulUnitTest(320,8);
    mulUnitTest(330,8);
    mulUnitTest(340,8);
    mulUnitTest(350,8);
    mulUnitTest(360,8);
    mulUnitTest(370,8);
    mulUnitTest(380,8);
    mulUnitTest(390,8);
    mulUnitTest(400,8);
    mulUnitTest(410,8);
    mulUnitTest(420,8);
    mulUnitTest(430,8);
    mulUnitTest(440,8);
    mulUnitTest(450,8);
    mulUnitTest(460,8);
    mulUnitTest(470,8);
    mulUnitTest(480,8);
    mulUnitTest(490,8);


    std::cerr<<"Zmienny wykladnik stala mantysa"<<std::endl;
    populationSize = 10;

    mulUnitTest(200,8);
    mulUnitTest(200,16);
    mulUnitTest(200,24);
    mulUnitTest(200,32);
    mulUnitTest(200,40);
    mulUnitTest(200,48);
    mulUnitTest(200,56);
    mulUnitTest(200,64);
}

void divTestCombo(){

    //generate population
    int populationSize = 40;
    std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);

    std::cerr<<"Dzielenie"<<std::endl;
    std::cerr<<"Zmienna mantsa staly wykladnik"<<std::endl;

    divUnitTest(20,8);
    divUnitTest(30,8);
    divUnitTest(40,8);
    divUnitTest(50,8);
    divUnitTest(60,8);
    divUnitTest(70,8);
    divUnitTest(80,8);
    divUnitTest(90,8);
    divUnitTest(100,8);
    divUnitTest(110,8);
    divUnitTest(120,8);
    divUnitTest(130,8);
    divUnitTest(140,8);
    divUnitTest(150,8);
    divUnitTest(160,8);
    divUnitTest(170,8);
    divUnitTest(180,8);
    divUnitTest(190,8);
    divUnitTest(200,8);
    divUnitTest(210,8);
    divUnitTest(220,8);
    divUnitTest(230,8);
    divUnitTest(240,8);
    divUnitTest(250,8);
    divUnitTest(260,8);
    divUnitTest(270,8);
    divUnitTest(280,8);
    divUnitTest(290,8);
    divUnitTest(300,8);
    divUnitTest(310,8);
    divUnitTest(320,8);
    divUnitTest(330,8);
    divUnitTest(340,8);
    divUnitTest(350,8);
    divUnitTest(360,8);
    divUnitTest(370,8);
    divUnitTest(380,8);
    divUnitTest(390,8);
    divUnitTest(400,8);
    divUnitTest(410,8);
    divUnitTest(420,8);
    divUnitTest(430,8);
    divUnitTest(440,8);
    divUnitTest(450,8);
    divUnitTest(460,8);
    divUnitTest(470,8);
    divUnitTest(480,8);
    divUnitTest(490,8);


    std::cerr<<"Zmienny wykladnik stala mantysa"<<std::endl;
    populationSize = 10;

    divUnitTest(200,8);
    divUnitTest(200,16);
    divUnitTest(200,24);
    divUnitTest(200,32);
    divUnitTest(200,40);
    divUnitTest(200,48);
    divUnitTest(200,56);
    divUnitTest(200,64);
}

int main()
{
    srand(time(NULL));

    addTestCombo();
    subTestCombo();
    mulTestCombo();
    divTestCombo();
    sqrtTestCombo();


    //int populationSize = 2;
    //std::vector<float> randomFloats = Test::generateRandomFloats(populationSize, 0xfffffff,0,1000);
    //addUnitTest(200,64);

    return 0;


    //create floats from population
    /*VariableFloat<104, 18> data3[populationSize];
    AddTest<104,18> add3(data3);
    fillArray(data3, populationSize, randomFloats);
    runTest(add3, data3, populationSize);

    VariableFloat<53, 11> g(0.047);
    std::cout << VariableFloat<53, 11>::sqrt(g) << std::endl;

    //std::cout<<"czas testow (bez after i before): "<<std::fixed<<result.fullTimeOfTests<<std::endl;

    VariableFloat<23, 8> f(false, "03", "9570A4");
    VariableFloat<23, 8> h(false, "02", "C851EC");

    std::cout << f / h << std::endl;*/

    return 0;
}


