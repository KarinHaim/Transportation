
#ifndef TRANSPORTATION_LOCATION_H
#define TRANSPORTATION_LOCATION_H

#include "Point.h"

/**
 * this function defines the location of each ekement.
 */
 using namespace std;
class Location {
    //serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & position;
    }
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