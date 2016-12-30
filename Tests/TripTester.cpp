#include <gtest/gtest.h>
#include "../Trip.h"

/*
 * TripTester is a test fixture class which includes tests of Trip class using
 * Google's Testing Framework.
 */
class TripTester : public testing::Test {
protected:
    Map* map;
    Trip* trip;
    Point* point;
    Location* location;
    //Initializes the needed variables each time a test is executed.
    virtual void SetUp() {
        trip = new Trip(123, Point(5,5), Point(1,2), map, 3, 5, 0);
        point = new Point(5,5);
        location = new Location(point);
        trip->setLocation(location);
    }

    virtual void TearDown() {
        delete(trip);
        delete(location);
        delete(point);
    }
public:
    //A constructor
    TripTester() {
        map = new Map(20,20);
    }
    ~TripTester() {
        delete(map);
    }
};

/**
 * This function tests that 'move' updates the correct move of 'trip'.
 * ('move' function simply operates the "moveOneStep" function of "Road").
 */

TEST_F(TripTester, moveTester) {
    //this returns the index of the current location in the vector
    int i;
    for(i = 0; i < trip->getRoad()->getRoad().size(); i++) {
        if(trip->getRoad()->getRoad()[i] == location->getPosition())
            break;
    }
    trip->getRoad()->moveOneStep();
    //now the current location should be the vector at index 'index+1'.
    EXPECT_EQ(trip->getRoad()->getCurrentLocation()->getPosition(),
              trip->getRoad()->getRoad()[i+1]);
}

//this function tests that "moveToEnd" function takes the trip to its final stop.
TEST_F(TripTester, moveToEndTester) {
    trip->moveToEnd();
    EXPECT_EQ(*(trip->getCurrentLocation()->getPosition()), Point(1,2));
}