#include "StandardCab.h"

/**
 * this function is a constructor for a new StandardCab.
 */
StandardCab::StandardCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff): Cab(id, speed, manufacturer, color, tariff) {
}

/**
 * this function is a default constructor for a new StandardCab.
 */
StandardCab::StandardCab(): Cab() {
}

/**
 * this function is the destructor of a StandardCab.
 */
StandardCab::~StandardCab() {
}

/**
 * this function returns if the Cab is occupied at the moment.
 * @return a boolean value representing the answer.
 */
bool StandardCab::getIsOccupied() {
    return this->isOccupied;
}

/**
 * this function sets the occupation of the cab.
 * @param occupation - the new occupation.
 */
void StandardCab::setOccupation(bool occupation) {
    this->isOccupied = occupation;
}

/**
 * this function returns this cab's tariff.
 * @return the tariff.
 */
double StandardCab::getTariff() {
    return this->tariff;
}

/**
 * this function returns this cab's ID.
 * @return the ID.
 */
int StandardCab::getID() {
    return this->id;
}

//BOOST_CLASS_EXPORT(StandardCab)