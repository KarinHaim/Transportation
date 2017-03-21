#include "../headers/TaxiCenter.h"
#include "../headers/easylogging++.h"

/**
 * this function is a constructor of TaxiCenter.
 */
TaxiCenter::TaxiCenter() {
    this->map = Map();
    this->allMoney = 0;
    this->clock = new Clock();
    threadPool = new ThreadPool(5);
}

/**
 * this function is a destructor of taxi center.
 */
TaxiCenter::~TaxiCenter() {
    int size = tasks.size();
    for (int i = 0; i < size; i++)
        delete tasks[i];
    size = calculateRoads.size();
    for (int i = 0; i < size; i++)
        delete calculateRoads[i];
    delete threadPool;

    for (int i = 0; i < this->drivers.size(); i++) {
        delete(this->drivers[i]);
    }
    for (int i = 0; i < this->cabs.size(); i++) {
        delete(this->cabs[i]);
    }

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
void TaxiCenter::setMap(Map& map) {
    this->map = map;
    LOG(DEBUG) << "taxi center's map is " << &this->map << "\n";
}

/**
 * this function add a driver to the taxi center.
 * @param driver - the driver to be added.
 */
void TaxiCenter::addDriver(Driver* driver) {
    //check if the driver's id already exists
    /*for (int i = 0; i < this->drivers.size(); i++) {
        if(this->drivers[i]->getID() == driver->getID())
            throw "driver with this id was already inserted";
    }*/
    this->drivers.push_back(driver);

    this->locations[driver->getID()] = driver->getLocation();
    LOG(DEBUG) << "driver's location is " << driver->getLocation() << "\n";
    LOG(DEBUG) <<  "driver's location point is " << driver->getLocation()->getPosition();
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
    /*if (std::find(this->drivers.begin(), this->drivers.end(),driver) == this->drivers.end()) {
        //means the driver not found
        throw "driver not found";
    }*/
    for (int i = 0; i < this->cabs.size(); i++) {
        if(this->cabs[i]->getID() == cabID) {
            driver->attachCab(this->cabs[i]);
            this->cabs[i]->setOccupation(true);
            return cabs[i];
        }
    }
    //throw "cab with id not found";
}

/**
 * this function add a trip to the taxi center.
 * @param trip
 */
void TaxiCenter::addTrip(Trip* trip) {
    for (int i = 0; i < this->trips.size(); i++) {
        if (this->trips[i]->getID() == trip->getID())
            throw "trip with this id was already inserted";
    }
    this->trips.push_back(trip);

    CalculateRoadThread *calculateRoad = new CalculateRoadThread(trip, this->map);
    calculateRoads.push_back(calculateRoad);
    Task *calculateTripsRoad = new Task(CalculateRoadThread::callCalculateRoad, calculateRoad);
    tasks.push_back(calculateTripsRoad);
    threadPool->addTask(calculateTripsRoad);
}


/**
 * this function attaches the trips to the drivers.
 *
 */
 std::vector<Driver*> TaxiCenter::attachTripsToDrivers() {
    std::vector<Driver*> attachedTripsDrivers;
    for(int i = 0; i < this->trips.size(); i++) {
        if (this->trips[i]->getStartTime() == this->clock->getCurrentTime()) {
            /**
             * when the time of the trip arrives, wait until it's calculation of road is done and
             * then check if there is an available route. if not, delete the trip before matching a
             * driver.
             */
             while(!this->trips[i]->getRoad()->isFinishedCalculationOfRoad()) {
                 sleep(1);
             }
            //means that a route was not found.
            if (this->trips[i]->getRoad()->getRoad().empty()) {
                this->trips.erase(this->trips.begin() + i);
                continue;
            }
            for(int j = 0; j < this->drivers.size(); j++) {
                //check if the driver is available
                if(this->drivers[j]->getTrip() == NULL) {
                    //check if the driver is in the same point as the start of the trip
                    if (this->drivers[j]->getLocation()->getPosition() == this->trips[i]->getStartP()) {
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
    std::map<int, Location*>::iterator it = this->locations.find(driverID);
    //means the id have not found
    if(it == this->locations.end())
        throw "id not exist";
    Location* location = it->second;
    LOG(DEBUG) << "location is " << location << "\n";
    Point point = location->getPosition();
    LOG(DEBUG) << "point is %p\n" << point << "\n";
    return point;
    //LOG(DEBUG) << "location is " << this->locations.find(driverID)->second->getPosition();
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
Map TaxiCenter::getMap() {
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
