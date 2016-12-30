
#ifndef TRANSPORTATION_TRIP_H
#define TRANSPORTATION_TRIP_H

#include "Point.h"
#include "Map.h"
#include "Road.h"
#include "Location.h"
#include "Passenger.h"
#include "Clock.h"

using namespace std;
/**
 * this class defines a trip with start and end points, number of passengers etc.
 */
class Trip {
    //serialization
    friend class boost::serialization::access;
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
        ar & startTime;
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
    int startTime;
public:
    Trip(int id, Point start, Point end, Map* map, int passengers, double tariff, int startTime);
    Trip();
    ~Trip();
    Location* getCurrentLocation();
    double getTariff();
    void move(int speed);
    Road* getRoad();
    int getPassengersNum();
    void addMetersPassed(int meters);
    std::vector<Passenger*> getPassengers();
    Point getStartP();
    Point getEndP();
    int getID();
    void setLocation(Location* location);
    int getStartTime();
};




#endif //TRANSPORTATION_TRIP_H