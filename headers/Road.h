
#ifndef TRANSPORTATION_ROAD_H
#define TRANSPORTATION_ROAD_H

#include "Map.h"
#include "Location.h"
#include "Point.h"
#include <vector>

using namespace std;

/**
 * this class defines a Road.
 */
class Road {
    //serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & start;
        ar & end;
        ar & currentLocation;
        ar & road;
    }
private:
    Point start;
    Point end;
    Location* currentLocation;
    std::vector<Point> road;
    bool isDoneCalculationOfRoad;
public:
    Road(Map& map, Point start, Point end);
    Road();
    ~Road();
    Location* getCurrentLocation();
    std::vector<Point> getRoad();
    void moveOneStep();
    void setLocation(Location* location);
    Point getStart();
    Point getEnd();
    void setRoad(std::vector<Point> paramRoad);
    void setCalculationOfRoadToDone();
    bool isFinishedCalculationOfRoad();
};

#endif //TRANSPORTATION_ROAD_H