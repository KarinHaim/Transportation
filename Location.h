
#ifndef TRANSPORTATION_LOCATION_H
#define TRANSPORTATION_LOCATION_H

#include "Point.h"

/**
 * this function defines the location of each ekement.
 */
class Location {
private:
    Point* position;
public:
    Location(Point* position);
    Location();
    ~Location();
    void updateLocation(Point* newPosition);
    Point* getPosition();
};


#endif //TRANSPORTATION_LOCATION_H
