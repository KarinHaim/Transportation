
#ifndef TRANSPORTATION_LOCATION_H
#define TRANSPORTATION_LOCATION_H

#include "Point.h"
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/assume_abstract.hpp>
//#include <boost/serialization>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

/**
 * this function defines the location of each ekement.
 */
 using namespace std;
class Location {
    //serialization
    friend class boost::serialization::access;
//    friend ostream & operator<<(ostream &os, const Location &location);
//    friend ostream & operator<<(ostream &os, const Location *location);
//    friend istream & operator>>(istream &input, const Location &location);
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

/*ostream & operator<<(ostream &os, const Location &location) {
    os << location.position;
}*/


#endif //TRANSPORTATION_LOCATION_H
