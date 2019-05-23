#include "Test.h"

Test::TestResult Test::createTest(UnitTimeTest &unitTest, int testCount)
{
    TestResult ret{};
    ret.testCount = testCount;
    double timeOfTests = 0;
    Timer fullTime;

    fullTime.start();

    for (int i = 0; i < testCount; ++i)
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
    ret.avgTimePerTest = ret.fullTimeOfTests  / ret.testCount;
    return ret;
}