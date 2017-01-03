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

BOOST_CLASS_EXPORT(StandardCab)