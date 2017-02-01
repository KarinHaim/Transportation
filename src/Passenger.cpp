#include "../headers/Passenger.h"

/**
 * this function is a counstructor of the passenger class.
 * @param source - the source point of the passenger.
 * @param destination - the destination point of the passenger.
 */
Passenger::Passenger(Point source, Point destination) {
    this->sourceP = source;
    this->destinationP = destination;
    this->money = 0;
}

/**
 * this is a default constructor.
 */
Passenger::Passenger() {
    this->sourceP = Point();
    this->destinationP = Point();
    this->money = 0;
}

/**
 * this function is a destructor.
 */
Passenger::~Passenger() {

}

/**
 * this function generates a rendom number between 1 and 5 which is the satisfaction score
 * of the passenger about this trip.
 * @return - the random score.
 */
int Passenger::getSatisfactionScore() {
    srand (time(NULL));
    //generate a number between 1 and 5
    return rand() % 5 + 1;
}

/**
 * this function sets the money of the passenger.
 * @param newMoney - the money to be updated.
 */
void Passenger::setMoney(double newMoney){
    this->money = newMoney;
}

/**
 * this function pays the driver, meaning it reduces the passenger's money.
 * @param finalTariff - the tariff to pay.
 */
/*void Passenger::pay(double finalTariff) {
    if((this->money - finalTariff) <= 0)
        this->money = 0;
    else {
        this->money = this->money - finalTariff;
    }
}*/

/**
 * this function returns the money the passenger currently has.
 * @return
 */
double Passenger::getMoney() {
    return this->money;
}