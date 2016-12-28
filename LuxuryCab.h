
#ifndef TRANSPORTATION_LUXURYCAB_H
#define TRANSPORTATION_LUXURYCAB_H

#include "Cab.h"

/**
 * this class defines a LuxuryCab which is a derived class of "Cab".
 */
class LuxuryCab : public Cab {
public:
    LuxuryCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff);
    LuxuryCab();
    ~LuxuryCab();
    bool getIsOccupied();
    void setOccupation(bool occupation);
    double getTariff();
    int getID();
};

#endif //TRANSPORTATION_LUXURYCAB_H
