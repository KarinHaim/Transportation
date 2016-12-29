
#ifndef TRANSPORTATION_TRIP_H
#define TRANSPORTATION_TRIP_H

#include "Point.h"
#include "Map.h"
#include "Road.h"
#include "Location.h"
#include "Passenger.h"

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
 * this class defines a trip with start and end points, number of passengers etc.
 */
class Trip {
    //serialization
    friend class boost::serialization::access;
    friend ostream & operator<<(ostream &os, const Trip &trip);
    friend ostream & operator<<(ostream &os, const Trip *trip);
    friend istream & operator>>(istream &input, const Trip &trip);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & metersPassed;
        ar & startP;
        ar & endP;
        ar & map;
        ar & passengersNum;
        ar & tariff;
        ar & currentLocation;
        ar & road;
        ar & passengers;
    }
private:
    int id;
    int metersPassed;
    Point startP;
    Point endP;
    Map* map;
    int passengersNum;
    double tariff;
    Location* currentLocation;
    Road road;
    std::vector<Passenger*> passengers; //constructs an empty list of passenger*.
    void initializePassengers();
public:
    Trip(int id, Point start, Point end, Map* map, int passengers, double tariff);
    Trip();
    ~Trip();
    Location* getCurrentLocation();
    double getTariff();
    void move();
    void moveToEnd();
    Road* getRoad();
    int getPassengersNum();
    void addMetersPassed(int meters);
    std::vector<Passenger*> getPassengers();
    Point getStartP();
    int getID();
    void setLocation(Location* location);
};




#endif //TRANSPORTATION_TRIP_H