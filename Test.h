#ifndef TEST_H
#define TEST_H

#include "Timer.h"

/**
 * @brief The UnitTimeTest class virtual class which allow Tests class to run tested function
 */
class UnitTimeTest{
public:

    /**
     * @brief runTest tested function.
     */
    virtual void runTest() = 0;

    /**
     * @brief runBeforeTest
     */
    virtual void runBeforeTest(){}

    /**
     * @brief runAfterTest
     */
    virtual void runAfterTest(){}
};

class Test
{
public:
    /**
     * @brief The TestResult class
     */
    class TestResult{
    public:
        double fullTime;
        double fullTimeOfTests;
        int testCount;
    };

    Test(){}

    /**
     * @brief createTest runs tested function.
     * @param unitTest
     * @return
     */
    TestResult createTest(UnitTimeTest& unitTest, int testCount){
        TestResult ret;
        ret.testCount = testCount;
        double timeOfTests = 0;
        Timer fullTime;

        fullTime.start();

        for(int i=0;i<testCount;++i){
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


#endif // TEST_H
