
#ifndef TRANSPORTATION_TRIP_H
#define TRANSPORTATION_TRIP_H

#include "Point.h"
#include "Map.h"
#include "Road.h"
#include "Location.h"
#include "Passenger.h"
/**
 * this class defines a trip with start and end points, number of passengers etc.
 */
class Trip {
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