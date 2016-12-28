#include <gtest/gtest.h>
#include "../Point.h"

/*
 * PointTester is a test fixture class which includes tests of Point class using
 * Google's Testing Framework.
 */
class PointTester : public testing::Test {
protected:
    Point p1, p2;
    //Initializes the needed variables each time a test is executed.
    virtual void SetUp() {
        p1 = Point(3,5);
        p2 = Point(6,5);
    }
public:
    //A constructor
    PointTester() {}
};

//This function tests the operator function works as expected.
TEST_F(PointTester, EqualOperatorTester) {
    EXPECT_FALSE(p1 == p2);
}

//This function tests the operator function works as expected.
TEST_F(PointTester, NotEqualOperatorTester) {
    p2 = Point(3,5);
    EXPECT_FALSE(p1 != p2);
}

//The function tests that OutputOperator function puts the correct string in output stream.
TEST_F(PointTester, OutputOperatorTester) {
    std::ostringstream output;
    output << p1;
    std::ostringstream expectedOutput;
    expectedOutput << "(" << p1.getX() << "," << p1.getY() << ")" << std::endl;
    EXPECT_EQ(expectedOutput.str(), output.str());
}