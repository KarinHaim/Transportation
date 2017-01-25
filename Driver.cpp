
#include "Driver.h"
#include "easylogging++.h"

/**
 * this function is a constructor of driver.
 * @param id - the id of the driver.
 * @param age  - the age of the driver.
 * @param meritalStatus - the merital status of the driver.
 * @param yearsOfExp - the years of experiance of the driver.
 */
Driver::Driver(int id, int age, MeritalStatus meritalStatus, int yearsOfExp, int cabID) {
    this->id = id;
    this->age = age;
    this->meritalStatus = meritalStatus;
    this->yearsOfExp = yearsOfExp;
    this->cabID = cabID;

    //everything else is initialized to 0 or NULL
    this->avgSatisfaction = 0;
    this->finalTariff = 0;
    this->money = 0;
    this->totalNumOfPassengers = 0;
    this->cab = NULL;
    this->startingPoint = new Point(0,0);
    LOG(DEBUG) << "starting point is " << this->startingPoint << "\n";
    LOG(DEBUG) << *this->startingPoint << "\n";
    this->location = new Location(startingPoint);
    this->trip = NULL;
}

//this function is a default constructor for Driver.
Driver::Driver() {
    this->id = 0;
    this->age = 0;
    this->meritalStatus = MeritalStatus::SINGLE;
    this->yearsOfExp = 0;

    //everything else is initialized to 0 or NULL
    this->avgSatisfaction = 0;
    this->finalTariff = 0;
    this->money = 0;
    this->totalNumOfPassengers = 0;
    this->cab = NULL;
    this->startingPoint = NULL;
    this->location = NULL;
    this->trip = NULL;
}

/**
 * a destructor of the driver.
 */
Driver::~Driver() {
    if (this->trip != NULL)
        delete(this->trip);
    if (this-> location!= NULL)
        delete(this->location);
    delete(startingPoint);
}

/**
 * this function updates the trip to the driver.
 * @param trip - the trip to be updated.
 */
void Driver::updateTrip(Trip* trip) {
    if (this->trip != NULL)
        delete(this->trip);
    this->trip = trip;
    this->trip->setLocation(this->location);
    LOG(DEBUG) << "location of trip is " << *(this->trip->getCurrentLocation()->getPosition());
    this->totalNumOfPassengers = this->totalNumOfPassengers + trip->getPassengersNum();
}

/**
 * this function attach the driver a cab.
 * @param cab - the cab to be attached.
 */
void Driver::attachCab(Cab* cab) {
    this->cab = cab;
}

/*
void Driver::addPassenger(Passenger* passenger) {
    this->passengers.push_back(passenger);
    this->totalNumOfPassengers++;
}*/

/**
 * this function sets the driver's location.
 * @param location - the new location.
 */
void Driver::updateLocation(Point* location) {
    this->location->updateLocation(location);
}

/**
 * this function calculates the final tariff of the ride.
 */
void Driver::calculateFinalTariff() {
    this->finalTariff = this->trip->getTariff()*this->cab->getTariff();
}

/**
 * this function pays the driver.
 * @param cash
 */
/*void Driver::getPaid(double cash) {
    this->money = this->money + cash;
}*/

/**
 * this function resets the money of the driver to 0.
 */
/*void Driver::resetMoney() {
    this->money = 0;
}*/

/**
 * this function takes the money of all the passengers the driver has at the moment.
 */
/*void Driver::getMoneyFromPassengers() {
    /*double moneyForEach = this->finalTariff / this->passengers.size();
    for (int i = 0; i <= this->passengers.size(); i++) {
        this->passengers[i]->pay(moneyForEach); //reduces money from passenger
    }
    this->getPaid(this->finalTariff);*/
/*
    double moneyForEach = this->finalTariff / this->trip->getPassengersNum();
    std::vector<Passenger*> passengers = trip->getPassengers();
    for (int i = 0; i < passengers.size(); i++) {
        passengers[i]->pay(moneyForEach); //reduces money from passenger
    }
    this->getPaid(this->finalTariff);
}*/

/**
 * this function calculates the avg satisfaction of the driver.
 */
void Driver::calculateAvgSatisfaction() {
    /*for (int i = 0; i <= this->passengers.size(); i++) {
        this->scoresSum += this->passengers[i]->getSatisfactionScore();
    }
    this->avgSatisfaction = this->scoresSum / totalNumOfPassengers;*/
    int totalSatisfactionScore = avgSatisfaction * (totalNumOfPassengers - this->trip->getPassengersNum());
    std::vector<Passenger*> passengers = trip->getPassengers();
    for (int i = 0; i < passengers.size(); i++) {
        totalSatisfactionScore += passengers[i]->getSatisfactionScore();
    }
    avgSatisfaction = totalSatisfactionScore / this->totalNumOfPassengers;
}

/**
 * this function move one step all drivers..
 */
void Driver::move() {
    if (this->trip != NULL) {
        this->trip->move(this->cab->getSpeed());
        if (*this->location->getPosition() == this->trip->getEndP()) {
            delete(this->trip);
            this->trip = NULL;
        }
    }
}

/**
 * this function returns the id of the driver.
 * @return the id
 */
int Driver::getID() {
    return id;
}

/**
 * this function returns the age of the driver.
 * @return the age
 */
int Driver::getAge() {
    return age;
}

/**
 * this function returns the merital status of the driver.
 * @return the merital status
 */
MeritalStatus Driver::getMeritalStatus() {
    return meritalStatus;
}

/**
 * this function returns the years of experiance of the driver.
 * @return the years
 */
int Driver::getYearsOfExp() {
    return yearsOfExp;
}

/**
 * this function returns the avg satisfaction of the driver.
 * @return the avg satisfaction.
 */
int Driver::getAvgSatisfaction() {
    return avgSatisfaction;
}
/*
std::vector<Passenger*> Driver::getPassengers() {
    return passengers;
}*/

/**
 * this function returns the cab of the driver.
 * @return the cab
 */
Cab * Driver::getCab() {
    return cab;
}

/**
 * this function returns the final tariff of the trip.
 * @return the final tariff.
 */
double Driver::getFinalTariff() {
    return finalTariff;
}

/**
 * this function returns the trip of the driver.
 * @return the trip
 */
Trip* Driver::getTrip() {
    return trip;
}

/**
 * this function returns the location of the driver.
 * @return the location
 */
Location* Driver::getLocation() {
    return location;
}

/**
 * this function returns the money of the driver.
 * @return the money
 */
double Driver::getMoney() {
    return money;
}

/**
 * this function returns the cab id of the driver.
 * @return
 */
int Driver::getCabID() {
    return cabID;
}