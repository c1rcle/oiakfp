#pragma once

#include "../util/Timer.h"
#include "../VariableFloat.h"

#include "stdio.h"



///
class UnitTimeTest
{
public:

    ///
    virtual void runTest() = 0;

    ///
    virtual void runBeforeTest() {}

    ///
    virtual void runAfterTest() {}
};


class Test
{
public:

    ///
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


    ///
    Test() = default;

    ///
    /// \param unitTest
    /// \param testCount
    /// \return
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



/**
 * @brief fillArray fills floats created by default constructor with random data in range of
 *        <max/point, min/point>
 * @param array pointer to Variable float array
 * @param size size of array
 * @param max
 * @param min
 * @param point is the decimal point position in random generated number
 */
template<int fraction, int exponent>
void fillArray(VariableFloat<fraction, exponent> array[], int size, const std::vector<float> data)
{
    for(int i=0;i<size && i<data.size();++i)
        array[i] = VariableFloat<fraction, exponent>(data[i]);
}
