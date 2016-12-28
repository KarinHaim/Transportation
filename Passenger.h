
#ifndef TRANSPORTATION_PASSENGER_H
#define TRANSPORTATION_PASSENGER_H

#include "Point.h"

/**
 * this class defines a passenger.
 */
class Passenger {
private:
    Point sourceP;
    Point destinationP;
    double money;
public:
    Passenger(Point source, Point destination);
    Passenger();
    ~Passenger();
    int getSatisfactionScore();
    void setMoney(double newMoney);
   // void pay(double finalTariff);
    double getMoney();
};


#endif //TRANSPORTATION_PASSENGER_H
