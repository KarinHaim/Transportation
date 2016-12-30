#include "Trip.h"

/**
 * this function is a constructor.
 * @param id - id of the trip
 * @param start - start point of the trip
 * @param end - end point of the trip
 * @param map - map of the trip
 * @param passengers - number of passengers of the trip
 * @param tariff - the tariff of the trip
 */
Trip::Trip(int id, Point start, Point end, Map* map, int passengers, double tariff, int startTime) {
    this->id = id;
    this->metersPassed = 0;
    this->startP = start;
    this->endP = end;
    this->map = map;
    this->passengersNum = passengers;
    this->tariff = tariff;
    this->road = Road(map, start, end);
    this->initializePassengers();
    this->currentLocation = NULL;
    this->startTime = startTime;
}

/**
 * this function is a default constructor.
 * @param id - id of the trip
 * @param start - start point of the trip
 * @param end - end point of the trip
 * @param map - map of the trip
 * @param passengers - number of passengers of the trip
 * @param tariff - the tariff of the trip
 */
Trip::Trip() {
    this->id = 0;
    this->metersPassed = 0;
    this->startP = Point();
    this->endP = Point();
    this->map = NULL;
    this->passengersNum = 0;
    this->tariff = 0;
    this->road = Road();
    this->currentLocation = NULL;
    this->startTime = 0;
}

/**
 * this function is a destructor.
 */
Trip::~Trip() {
    //deleting the list of passengers
    /*for (std::vector<Passenger*>::iterator it=this->passengers.begin(); it != this->passengers.end(); ++it)
        delete(*it);*/
    for (int i=0; i<this->passengers.size(); i++)
        delete(passengers[i]);
}

/**
 * this function initializes the passengers of the trip.
 */
void Trip::initializePassengers() {
    this->passengers = std::vector<Passenger*>();
    for (int i=0; i<passengersNum; i++) {
        this->passengers.push_back(new Passenger(startP, endP));
    }
}

/**
 * this function returns the current location of the trip.
 * @return - the current location.
 */
Location* Trip::getCurrentLocation() {
    return this->road.getCurrentLocation();
}

/**
 * this function returns the tariff of the trip.
 * @return - the tariff.
 */
double Trip::getTariff() {
    return this->tariff;
}

/**
 * this function moves the trip one step ahead.
 */
void Trip::move(int speed) {
    for (int i = 0; i < speed; i++) {
        if (*this->road.getCurrentLocation()->getPosition() != this->endP) {
            this->road.moveOneStep();
            this->addMetersPassed(1);
        }
    }
}

/**
 * this function returns the road of the trip.
 * @return - the road.
 */
Road* Trip::getRoad() {
    return &this->road;
}

/**
 * this function returns the number of passengers of the trip.
 * @return - number of passengers.
 */
int Trip::getPassengersNum() {
    return this->passengersNum;
}

/**
 * this function adds a meters to the counter of meters passed of the trip.
 * @param meters - the meters to be added.
 */
void Trip::addMetersPassed(int meters) {
    this->metersPassed = this->metersPassed + meters;
}

/**
 * this function returns the passengers of the trip.
 * @return - a vector of passengers.
 */
std::vector<Passenger*> Trip::getPassengers() {
    return this->passengers;
}

/**
 * this function returns the start point of the trip.
 * @return - the start point.
 */
Point Trip::getStartP() {
    return this->startP;
}

Point Trip::getEndP() {
    return this->endP;
}

/**
 * this function returns the ID of the trip.
 * @return
 */
int Trip::getID() {
    return this->id;
}

/**
 * this function sets the currentLocation and it's road currentLocation.
 * @param location- the location to set.
 */
void Trip::setLocation(Location* location) {
    this->currentLocation = location;
    this->road.setLocation(location);
}

/**
 * this function returns the starting time of the trip.
 * @return - the starting time.
 */
int Trip::getStartTime() {
    return this->startTime;
}