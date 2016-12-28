
#ifndef TRANSPORTATION_TAXICENTER_H
#define TRANSPORTATION_TAXICENTER_H

#include <list>
#include "Driver.h"
#include "Map.h"
#include "Point.h"
#include <map>
#include <vector>
#include "CarManufacturer.h"
#include "Color.h"
#include "Cab.h"

/**
 * this class defines the taxi center, which operates the database.
 */
class TaxiCenter {
private:
    Map* map;
    double allMoney;
    std::vector<Driver*> drivers;
    std::map<int, Location*> locations;
    std::vector<Cab*> cabs;
    std::vector<Trip*> trips;
public:
    TaxiCenter();
    ~TaxiCenter();
    void setMap(Map* map);
    void addDriver(Driver* driver);
    void addTaxi(Cab* cab);
    void attachTaxiToDriver(Driver* driver, int cabID);
    void addTrip(int id, Point start, Point end, int passengersNum, double tariff);
    void attachTripsToDrivers();
    Point getLocationOfDriver(int driverID);
    //double getAllMoney();
    //void recieveMoneyFromDrivers();
    std::vector<Driver*> getDrivers();
    std::vector<Cab*> getCabs();
    std::vector<Trip*> getTrips();
    Map* getMap();
    void startAllDrivers();
};

#endif //TRANSPORTATION_TAXICENTER_H
