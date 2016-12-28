
#ifndef TRANSPORTATION_ROAD_H
#define TRANSPORTATION_ROAD_H

#include "Map.h"
#include "Location.h"
#include "Point.h"
#include <vector>

/**
 * this class defines a Road.
 */
class Road {
private:
    Map* map;
    Point* start;
    Point* end;
    Location* currentLocation;
    std::vector<Point*> road;
    void calculateRoad(Point* start, Point* end);
public:
    Road(Map* map, Point start, Point end);
    Road();
    ~Road();
    Location* getCurrentLocation();
    std::vector<Point*> getRoad();
    void moveOneStep();
    void setLocation(Location* location);
};

#endif //TRANSPORTATION_ROAD_H