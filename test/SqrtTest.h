#pragma once

#include "Test.h"
#include <vector>
#include "../VariableFloat.h"

template<int fraction, int exponent>
class SqrtTest : public UnitTimeTest
{
protected:
    int testNb;
    VariableFloat<fraction, exponent>* data;
    VariableFloat<fraction, exponent>* currentA;
public:
    explicit SqrtTest(VariableFloat<fraction, exponent> *d) : testNb(0), data(d) {}

    void runTest() override
    {
        VariableFloat<fraction, exponent>::sqrt(*currentA);
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
