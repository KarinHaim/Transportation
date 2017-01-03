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
/*LuxuryCab::~LuxuryCab() {

}*/

//BOOST_CLASS_EXPORT(LuxuryCab)