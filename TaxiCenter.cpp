#include "TaxiCenter.h"
#include <algorithm>
#include <iterator>

/**
 * this function is a constructor of TaxiCenter.
 */
TaxiCenter::TaxiCenter() {
    this->map = NULL;
    this->allMoney = 0;
}

/**
 * this function is a destructor of taxi center.
 */
TaxiCenter::~TaxiCenter() {
    /*
    for (std::vector<Driver*>::iterator it=this->drivers.begin(); it != this->drivers.end(); ++it)
        delete(*it);
    for (std::vector<Cab*>::iterator it=this->cabs.begin(); it != this->cabs.end(); ++it)
        delete(*it);
        */
    for (int i = 0; i < this->drivers.size(); i++) {
        delete(this->drivers[i]);
    }
    for (int i = 0; i < this->cabs.size(); i++) {
        delete(this->cabs[i]);
    }
/*
    //delete locations of the map:
    std::map<int, Location*>::iterator it;
    for (it = this->locations.begin(); it != this->locations.end(); it++ )
        delete(it->second);*/

    //deletes the left trips
    for (int i = 0; i < this->trips.size(); i++) {
        delete(this->trips[i]);
    }
}

/**
 * this function sets the map member of taxi center.
 * @param map
 */
void TaxiCenter::setMap(Map* map) {
    this->map = map;
}

/**
 * this function add a driver to the taxi center.
 * @param driver - the driver to be added.
 */
void TaxiCenter::addDriver(Driver* driver) {
    //check if the driver's id already exists
    for (int i = 0; i < this->drivers.size(); i++) {
        if(this->drivers[i]->getID() == driver->getID())
            throw "driver with this id was already inserted";
    }
    this->drivers.push_back(driver);
    //finding the index of the cab
    //  attachTaxiToDriver(driver, cabID);

    this->locations[driver->getID()] = driver->getLocation();
}

/**
 * this function add a cab to the taxi center.
 * @param cab - the cab to be added.
 */
void TaxiCenter::addTaxi(Cab* cab) {
    //check if the cab's id is already exists
    for (int i = 0; i < this->cabs.size(); i++) {
        if(this->cabs[i]->getID() == cab->getID())
            throw "cab with this id was already inserted";
    }
    this->cabs.push_back(cab);
}

/**
 * this function attaches a taxi to a driver.
 * @param driver
 * @param cabID
 */
void TaxiCenter::attachTaxiToDriver(Driver* driver, int cabID) {
    if (std::find(this->drivers.begin(), this->drivers.end(),driver) == this->drivers.end()) {
        //means the driver not found
        throw "driver not found";
    }
    for (int i = 0; i < this->cabs.size(); i++) {
        if(this->cabs[i]->getID() == cabID) {
            driver->attachCab(this->cabs[i]);
            this->cabs[i]->setOccupation(true);
            break;
        }
    }
}

/**
 * this function add a trip to the taxi center.
 * @param id -id of the trip
 * @param start -start point of the trip
 * @param end - end point of the trip.
 * @param passengersNum - number of passengers in the trip.
 * @param tariff -the tariff of the trip.
 */
void TaxiCenter::addTrip(int id, Point start, Point end, int passengersNum, double tariff) {
    Trip* trip = new Trip(id, start, end, this->map, passengersNum, tariff);

    this->trips.push_back(trip);
}

/**
 * this function attaches the trips to the drivers.
 */
void TaxiCenter::attachTripsToDrivers() {
    for(int i = 0; i < this->trips.size(); i++) {
        for(int j = 0; j < this->drivers.size(); j++) {
            //check if the driver is available
            if(this->drivers[j]->getTrip() == NULL) {
                //check if the driver is in the same point as the start of the trip
                if (*(this->drivers[j]->getLocation()->getPosition()) == this->trips[i]->getStartP()) {
                    this->drivers[j]->updateTrip(this->trips[i]);
                    //  delete(this->trips[i]);
                    this->trips.erase(this->trips.begin() + i);
                }
            }
        }
    }
}

/**
 * this function returns the location of a specific driver.
 */
Point TaxiCenter::getLocationOfDriver(int driverID) {
    // return *(this->locations.find(driverID)->second->getPosition());
    for(int i = 0; i < this->drivers.size(); i++) {
        if (this->drivers[i]->getID() == driverID)
            return *(this->drivers[i]->getLocation()->getPosition());
    }
}

/**
 * this function returns the money amount in taxi center.
 * @return - the amount
 */
/*double TaxiCenter::getAllMoney() {
    return this->allMoney;
}*/

/**
 * this function charges from the drivers of the taxi center their money.
 */
/*void TaxiCenter::recieveMoneyFromDrivers() {
    for (int i = 0; i < this->drivers.size(); i++) {
        //add the driver's money to the taxi center
        this->allMoney = this->allMoney + this->drivers[i]->getMoney();
        //zero the driver's money
        this->drivers[i]->resetMoney();
    }
}*/

/**
 * this function returns the vector of all drivers in taxi center.
 * @return vector of drivers.
 */
std::vector<Driver*> TaxiCenter::getDrivers() {
    return this->drivers;
}

/**
 * this function returns the vector of all cabs in taxi center.
 * @return vector of cabs.
 */
std::vector<Cab*> TaxiCenter::getCabs() {
    return this->cabs;
}

/**
 * this function returns the map of the taxi center.
 * @return the map.
 */
Map* TaxiCenter::getMap() {
    return this->map;
}

/**
 * this function start moving all the drivers.
 */
void TaxiCenter::startAllDrivers() {
    for(int i = 0; i < this->drivers.size(); i++)
        this->drivers[i]->startDriving();
}

/**
 * this function returns a vector of the trips of the taxi center.
 * @return vector of trips.
 */
std::vector<Trip*> TaxiCenter::getTrips() {
    return this->trips;
}