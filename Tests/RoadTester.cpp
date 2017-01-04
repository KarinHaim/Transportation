/*
#include <gtest/gtest.h>
#include "../Road.h"

*/
/*
 * RoadTester is a test fixture class which includes tests of Road class using
 * Google's Testing Framework.
 *//*

class RoadTester : public testing::Test {
protected:
    Map* map;
    Road road;
    //Initializes the needed variables each time a test is executed.
    virtual void SetUp() {
        road = Road(map, Point(5,5), Point(3,3));
    }
public:
    //A constructor
    RoadTester(): road() {
        map = new Map(20,20);
    }
    ~RoadTester() {
        delete(map);
    }
};

//This function tests that 'moveOneStep' updates the correct move of 'Road'.
TEST_F(RoadTester, moveOneStepTester) {
    Location* location = new Location(map->getPointByCoordinates(Point(5,5)));
    road.setLocation(location);
    //this returns the index of the current location in the vector
    //  long index = find(road.getRoad().begin(), road.getRoad().end(), location->getLocation() - road.getRoad().begin();
    int i;
    for(i = 0; i < road.getRoad().size(); i++) {
        if(road.getRoad()[i] == location->getPosition())
            break;
    }

    */
/**
     * 'move one step' searches in the vector of points that represents the road in 'Road'
     * the current location and sets the new location to be the next point of the vector.
     *//*

    road.moveOneStep();
    //now the current location should be the vector at index 'index+1'.
    EXPECT_EQ(road.getCurrentLocation()->getPosition(), road.getRoad()[i+1]);
    delete(location);
}*/
