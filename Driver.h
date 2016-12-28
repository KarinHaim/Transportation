
#ifndef TRANSPORTATION_DRIVER_H
#define TRANSPORTATION_DRIVER_H

#include "Trip.h"
#include "Cab.h"
#include "Location.h"
#include "MeritalStatus.h"
/**
 * this class defines a driver.
 */
class Driver {
private:
    int id;
    int age;
    MeritalStatus meritalStatus;
    int yearsOfExp;
    int avgSatisfaction;
    Map* map;
    Cab *cab;
    double finalTariff;
    Trip *trip;
    Location *location;
    double money;
    int totalNumOfPassengers;
    void calculateAvgSatisfaction();
public:
    Driver(int id, int age, MeritalStatus meritalStatus, int yearsOfExp, Map* map);
    Driver();
    ~Driver();
    void updateTrip(Trip* trip);
    void attachCab(Cab * cab);
    //void addPassenger(Passenger* passenger);
    void updateLocation(Point* location);
    void calculateFinalTariff();
    //void getPaid(double cash);
    //void resetMoney(); //sets the money to 0
    //void getMoneyFromPassengers();
    void startDriving();

    //getters
    int getID();
    int getAge();
    MeritalStatus getMeritalStatus();
    int getYearsOfExp();
    int getAvgSatisfaction();
    //std::vector<Passenger*> getPassengers();
    Cab * getCab();
    double getFinalTariff();
    Trip* getTrip();
    Location* getLocation();
    double getMoney();

};

#endif //TRANSPORTATION_DRIVER_H
