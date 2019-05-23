#pragma once

#include "Test.h"
#include <vector>
#include "../VariableFloat.h"

template<int fraction, int exponent>
class DivTest : public UnitTimeTest
{
protected:
    int testNb;
    VariableFloat<fraction, exponent>* data;
    VariableFloat<fraction, exponent>* currentA;
    VariableFloat<fraction, exponent>* currentB;

public:
    explicit DivTest(VariableFloat<fraction, exponent> *d) : testNb(0), data(d) {}

    void runTest() override
    {
        (*currentA/(*currentB));
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