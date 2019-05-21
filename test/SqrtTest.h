#pragma once

#include "Test.h"
#include <vector>
#include "../VariableFloat.h"

///
/// \tparam fraction
/// \tparam exponent
template<int fraction, int exponent>
class SqrtTest : public UnitTimeTest
{
protected:
    int testNb;
    VariableFloat<fraction, exponent>* data;
    VariableFloat<fraction, exponent>* currentA;
    VariableFloat<fraction, exponent>* currentB;

public:
    ///
    /// \param d
    explicit SqrtTest(VariableFloat<fraction, exponent> *d) : testNb(0), data(d) {}

    void runTest() override
    {
        //currentA = currentA+currentB;
        VariableFloat<fraction, exponent>::sqrt(*currentA);
        //std::cout<<"test "<<testNb<<": "<<<<std::endl;
        //std::cout<<std::endl;
    }

    void runBeforeTest() override
    {
        currentA = &(data[2*testNb]);
    }

    void runAfterTest() override
    {
        testNb++;
    }
};
