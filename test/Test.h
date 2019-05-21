#pragma once

#include "../util/Timer.h"

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

///
class Test
{
public:

    ///
    class TestResult
    {
    public:
        double fullTime;
        double fullTimeOfTests;
        int testCount;
    };

    ///
    Test() = default;

    ///
    /// \param unitTest
    /// \param testCount
    /// \return
    TestResult createTest(UnitTimeTest& unitTest, int testCount)
    {
        TestResult ret{};
        ret.testCount = testCount;
        double timeOfTests = 0;
        Timer fullTime;

        fullTime.start();

        for(int i=0;i<testCount;++i)
        {
            unitTest.runBeforeTest();

            Timer tm;
            tm.start();

            unitTest.runTest();

            tm.stop();
            timeOfTests += tm.elapsed();
            unitTest.runAfterTest();
        }

        fullTime.stop();
        ret.fullTime = fullTime.elapsed();
        ret.fullTimeOfTests += timeOfTests;
        return ret;
    }
};