/*
#include <gtest/gtest.h>
#include "../Passenger.h"

*/
/*
 * PassengerTester is a test fixture class which includes tests of Passenger class using
 * Google's Testing Framework.
 *//*

class PassengerTester : public testing::Test {
protected:
    Passenger passenger;
    //Initializes the needed variables each time a test is executed.
    virtual void SetUp() {
        Passenger passenger = Passenger();
    }
public:
    //A constructor
    PassengerTester() {}
};

//This function tests that the function 'pay' reduces the current money member in 'passenger'.
*/
/*TEST_F(PassengerTester, payTester) {
    passenger.setMoney(100);
    //'pay' suppose to reduce the parameter from the 'money' member of Passenger.
    passenger.pay(20);
    //so these suppose to be equals now
    EXPECT_EQ(80, passenger.getMoney());
}*/
