#pragma once

#include "Test.h"
#include <vector>
#include "../VariableFloat.h"

///
/// \tparam fraction
/// \tparam exponent
template<int fraction, int exponent>
class SubTest : public UnitTimeTest
{
protected:
    int testNb;
    VariableFloat<fraction, exponent>* data;
    VariableFloat<fraction, exponent>* currentA;
    VariableFloat<fraction, exponent>* currentB;

public:
    ///
    /// \param d
    explicit SubTest(VariableFloat<fraction, exponent> *d) : testNb(0), data(d) {}

    void runTest() override
    {
        //currentA = currentA+currentB;
        std::cout<<"test "<<testNb<<":   "<<currentA->toBinary()<<std::endl;
        std::cout<<"test "<<testNb<<": - "<<currentB->toBinary()<<std::endl;
        std::cout<<"test "<<testNb<<": = "<<((*currentA)-(*currentB)).toBinary()<<std::endl;
        std::cout<<std::endl;
    }

    void runBeforeTest() override
    {
        currentA = &(data[2*testNb]);
        currentB = &(data[2*testNb+1]);
    }

    void runAfterTest() override
    {
        testNb++;
    }
};