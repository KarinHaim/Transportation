
#ifndef TRANSPORTATION_ROAD_H
#define TRANSPORTATION_ROAD_H

#include "Map.h"
#include "Location.h"
#include "Point.h"
#include <vector>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/**
 * this class defines a Road.
 */
class Road {
    //serialization
    friend class boost::serialization::access;
    friend ostream & operator<<(ostream &os, const Road &road);
    friend ostream & operator<<(ostream &os, const Road *road);
    friend istream & operator>>(istream &input, const Road &road);
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