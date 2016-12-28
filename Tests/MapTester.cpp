#include <gtest/gtest.h>
#include "../Map.h"

/*
 * MapTester is a test fixture class which includes tests of Map class using
 * Google's Testing Framework.
 */
class MapTester : public testing::Test {
protected:
    Map* map;
    //Initializes the needed variables each time a test is executed.
    virtual void SetUp() {
        map = new Map(4, 3);
    }
    virtual void TearDown() {
        delete(map);
    }
public:
    //A Constructor
    MapTester() {
    }
};

/*
 * this function tests that 'UpdateObstaclesTester' changes the field 'occupation'
 * of points that were defined as obstacles in the map.
 */
TEST_F(MapTester, UpdateObstaclesTester) {
    map->updateObstacles(std::vector<Point>(1, Point(1, 2)));
    EXPECT_EQ(true, map->getPointByCoordinates(Point(1, 2))->isOccupied());
}

//this function tests that map returns the corrent Point * for given coordinates.
TEST_F(MapTester, getPointByCoordinatesTester) {
    EXPECT_EQ(map->getPoints()[0][1], map->getPointByCoordinates(Point(0,1)));
}