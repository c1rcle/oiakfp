#ifndef ADDINGTEST_H
#define ADDINGTEST_H

#include "Test.h"
#include <vector>
#include "VariableFloat.h"

template<int fraction, int exponent>
class AddTest : public UnitTimeTest
{
protected:
    int testNb;
    VariableFloat<fraction, exponent>* data;

    VariableFloat<fraction, exponent>* currentA;
    VariableFloat<fraction, exponent>* currentB;

public:
    AddTest(VariableFloat<fraction, exponent> *d) : testNb(0), data(d) {}

    virtual void runTest(){
        //currentA = currentA+currentB;
        std::cout<<"test "<<testNb<<":   "<<currentA->toBinary()<<std::endl;
        std::cout<<"test "<<testNb<<": + "<<currentB->toBinary()<<std::endl;
        std::cout<<"test "<<testNb<<": = "<<(*currentA+*currentB).toBinary()<<std::endl;
        std::cout<<std::endl;
    }

    virtual void runBeforeTest(){
        currentA = &(data[2*testNb]);
        currentB = &(data[2*testNb+1]);
    }

    virtual void runAfterTest(){
        testNb++;
    }
};



#endif // ADDINGTEST_H
