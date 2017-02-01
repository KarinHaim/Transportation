#include "../headers/Cab.h"

/**
 * this function is a constructor for a new Cab.
 */
Cab::Cab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff) {
    this->id = id;
    this->speed = speed;
    this->manufacturer = manufacturer;
    this->color = color;
    this->tariff = tariff;
    this->isOccupied = false;
}

/**
 * this function is a default constructor for a Cab.
 */
Cab::Cab() {
    this->id = 0;
    this->speed = 0;
    this->tariff = 0;
    this->isOccupied = false;
}

/**
 * this function is the destructor of a Cab.
 */
Cab::~Cab() {
}

/**
 * this function returns if the Cab is occupied at the moment.
 * @return a boolean value representing the answer.
 */
bool Cab::getIsOccupied() {
    return this->isOccupied;
}

/**
 * this function sets the occupation of the cab.
 * @param occupation - the new occupation.
 */
void Cab::setOccupation(bool occupation) {
    this->isOccupied = occupation;
}

/**
 * this function returns this cab's tariff.
 * @return the tariff.
 */
double Cab::getTariff() {
    return this->tariff;
}

/**
 * this function returns this cab's ID.
 * @return the ID.
 */
int Cab::getID() {
    return this->id;
}

/**
 * this function returns the speed of the cab.
 * @return the speed.
 */
int Cab::getSpeed() {
    return this->speed;
}
