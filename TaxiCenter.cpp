#include "TaxiCenter.h"
#include "easylogging++.h"

/**
 * this function is a constructor of TaxiCenter.
 */
TaxiCenter::TaxiCenter() {
    this->map = NULL;
    this->allMoney = 0;
    this->clock = new Clock();
    pthread_mutex_init(&this->calculateRoadLocker, NULL);
}

/**
 * this function is a destructor of taxi center.
 */
TaxiCenter::~TaxiCenter() {
	for (std::map<int, CalculateRoadThread*>::iterator it = tripIdToCalculateRoadThreadMap.begin();
			it != tripIdToCalculateRoadThreadMap.end(); ++it) {
		delete it->second;
	}

    pthread_mutex_destroy(&this->calculateRoadLocker);

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
    delete(clock);
}

/**
 * this function sets the map member of taxi center.
 * @param map
 */
void TaxiCenter::setMap(Map* map) {
    this->map = map;
    LOG(DEBUG) << "taxi center's map is " << this->map << "\n";
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

    this->locations[driver->getID()] = driver->getLocation();
    LOG(DEBUG) << "driver's location is " << driver->getLocation() << "\n";
    LOG(DEBUG) <<  "driver's location point is " << *driver->getLocation()->getPosition();
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
Cab* TaxiCenter::attachTaxiToDriver(Driver* driver, int cabID) {
    if (std::find(this->drivers.begin(), this->drivers.end(),driver) == this->drivers.end()) {
        //means the driver not found
        throw "driver not found";
    }
    for (int i = 0; i < this->cabs.size(); i++) {
        if(this->cabs[i]->getID() == cabID) {
            driver->attachCab(this->cabs[i]);
            this->cabs[i]->setOccupation(true);
            return cabs[i];
        }
    }
    throw "cab with id not found";
}

/**
 * this function add a trip to the taxi center.
 * @param id -id of the trip
 * @param start -start point of the trip
 * @param end - end point of the trip.
 * @param passengersNum - number of passengers in the trip.
 * @param tariff -the tariff of the trip.
 */
void TaxiCenter::addTrip(int id, Point start, Point end, int passengersNum, double tariff,
                         int startTime) {
    Trip* trip = new Trip(id, start, end, this->map, passengersNum, tariff, startTime);

    this->trips.push_back(trip);

    LOG(DEBUG) << "taxi center's map before delivery to calculateroadthread " << this->map << "\n";

    CalculateRoadThread* calculateRoadThread = new CalculateRoadThread(&this->calculateRoadLocker,
                                                                       trip->getRoad(), this->map);
    calculateRoadThread->start();

    this->tripIdToCalculateRoadThreadMap[trip->getID()] = calculateRoadThread;


    //threadBfs.join();
  //  threadBfs.stop();

    //mutex and add the trip
   // pthread_mutex_lock(&this->addTripLocker);
    //this->trips.push_back(trip);
   // pthread_mutex_unlock(&this->addTripLocker);
}

/**
 * this function attaches the trips to the drivers.
 *
 */
 std::vector<Driver*> TaxiCenter::attachTripsToDrivers() {
    std::vector<Driver*> attachedTripsDrivers;
    for(int i = 0; i < this->trips.size(); i++) {
        if (this->trips[i]->getStartTime() == this->clock->getCurrentTime()) {
            for(int j = 0; j < this->drivers.size(); j++) {
                //check if the driver is available
                if(this->drivers[j]->getTrip() == NULL) {
                    //check if the driver is in the same point as the start of the trip
                    if (*(this->drivers[j]->getLocation()->getPosition()) == this->trips[i]->getStartP()) {
                        CalculateRoadThread* calculateRoadThread =
                              tripIdToCalculateRoadThreadMap.find(this->trips[i]->getID())->second;
                        (*calculateRoadThread).join();
                        this->drivers[j]->updateTrip(this->trips[i]);
                        attachedTripsDrivers.push_back(this->drivers[j]);
                        this->trips.erase(this->trips.begin() + i);
                        break;
                    }
                }
            }
        }
    }
    return attachedTripsDrivers;
}

/**
 * this function returns the location of a specific driver.
 */
Point TaxiCenter::getLocationOfDriver(int driverID) {
    Location* location = this->locations.find(driverID)->second;
    LOG(DEBUG) << "location is " << location << "\n";
    Point* point = location->getPosition();
    LOG(DEBUG) << "point is %p\n" << point << "\n";
    LOG(DEBUG) <<  "p is " << *point << "\n";
    return *point;
    //LOG(DEBUG) << "location is " << *(this->locations.find(driverID)->second->getPosition());
    //return *(this->locations.find(driverID)->second->getPosition());
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
/*void TaxiCenter::moveOneStepAllTrips() {
    for(int i = 0; i < this->trips.size(); i++)
        if (this->clock->getCurrentTime() < this->trips[i]->getStartTime()) {
            if (this->trips[i].get)//cab!
            this->trips[i].
        }
        this->drivers[i]->moveOneStep();
}*/

/**
 * this function returns a vector of the trips of the taxi center.
 * @return vector of trips.
 */
std::vector<Trip*> TaxiCenter::getTrips() {
    return this->trips;
}

/**
 * this function returns the current time of the world.
 * @return the current time.
 */
/*int TaxiCenter::getCurrentTime() {
    return this->clock->getCurrentTime();
}*/

/**
 * this function updates the current time of the world by 1.
 */
void TaxiCenter::updateTime() {
    this->clock->updateTime();
}

/**
 * this function returns the clock of the taxi center.
 * @return the clock
 */
Clock* TaxiCenter::getClock() {
    return this->clock;
}
