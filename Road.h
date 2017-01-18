
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
        ar & map;
        ar & start;
        ar & end;
        ar & currentLocation;
        ar & road;
    }
private:
    Map* map;
    Point* start;
    Point* end;
    Location* currentLocation;
    std::vector<Point*> road;
    pthread_mutex_t calculateRoadLocker;
public:
    Road(Map* map, Point start, Point end);
    Road();
    ~Road();
    Location* getCurrentLocation();
    std::vector<Point*> getRoad();
    void moveOneStep();
    void setLocation(Location* location);
    Point* getStartPCoordinates();
    Point* getEndPCoordinates();


    void setRoad(std::vector<Point*> paramRoad);
};
//static void calculateRoad(Road road);

#endif //TRANSPORTATION_ROAD_H