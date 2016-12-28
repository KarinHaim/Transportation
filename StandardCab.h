
#ifndef TRANSPORTATION_STANDARDCAB_H
#define TRANSPORTATION_STANDARDCAB_H

#include "Cab.h"

/**
 * this class defines a Standard Cab which inherits from Cab.
 */
class StandardCab : public Cab {
public:
    StandardCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff);
    StandardCab();
    ~StandardCab();
    bool getIsOccupied();
    void setOccupation(bool occupation);
    double getTariff();
    int getID();
};

#endif //TRANSPORTATION_STANDARDCAB_H
