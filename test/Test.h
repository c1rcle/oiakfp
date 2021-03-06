#pragma once

#include "../util/Timer.h"
#include "../VariableFloat.h"

#include "stdio.h"

class UnitTimeTest
{
public:

    virtual void runTest() = 0;

    virtual void runBeforeTest() {}

    virtual void runAfterTest() {}
};


class Test
{
public:

    class TestResult
    {
    public:
        double fullTime;
        double fullTimeOfTests;
        double avgTimePerTest;
        int testCount;
        int fraction;
        int exponent;

        void toCsv(std::ostream& str){
            str<<std::fixed<<fraction<<", "<<exponent<<", "<<fullTime<<","<<fullTimeOfTests<<","<<avgTimePerTest<<","<<testCount<<"\n";
        }
    };

    Test() = default;

    TestResult createTest(UnitTimeTest& unitTest, int testCount);

    static std::vector<float> generateRandomFloats(int size, int max, int min, int point){
        std::vector<float> ret;

        for(int i=0;i<size;++i){
            float buf = (rand()%(max-min)) + min;
            buf /= point;
            ret.push_back(buf);
        }

        return ret;
    }
};

template<int fraction, int exponent>
void fillArray(VariableFloat<fraction, exponent> array[], int size, const std::vector<float> &data)
{
    for(int i=0;i<size && i<data.size();++i)
        array[i] = VariableFloat<fraction, exponent>(data[i]);
}
