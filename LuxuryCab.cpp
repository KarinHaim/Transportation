#include "LuxuryCab.h"

/**
 * this function is a constructor for a new LuxuryCab.
 */
LuxuryCab::LuxuryCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff): Cab(id, speed, manufacturer, color, tariff) {
}

/**
 * this function is a default constructor for a new LuxuryCab.
 */
LuxuryCab::LuxuryCab(): Cab() {
}

/**
 * this function is the destructor of a Cab.
 */
LuxuryCab::~LuxuryCab() {

}

/**
 * this function returns if the Cab is occupied at the moment.
 * @return a boolean value representing the answer.
 */
bool LuxuryCab::getIsOccupied() {
    return this->isOccupied;
}

/**
 * this function sets the occupation of the cab.
 * @param occupation - the new occupation.
 */
void LuxuryCab::setOccupation(bool occupation) {
    this->isOccupied = occupation;
}


/**
 * this function returns this cab's tariff.
 * @return the tariff.
 */
double LuxuryCab::getTariff() {
    return this->tariff;
}

/**
 * this function returns this cab's ID.
 * @return the ID.
 */
int LuxuryCab::getID() {
    return this->id;
}

//BOOST_CLASS_EXPORT(LuxuryCab)