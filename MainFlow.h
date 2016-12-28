
#ifndef TRANSPORTATION_MAINFLOW_H
#define TRANSPORTATION_MAINFLOW_H

#include "TaxiCenter.h"
#include "Cab.h"
#include "Driver.h"
#include "Point.h"
#include "CarManufacturer.h"
#include "Color.h"
#include "MeritalStatus.h"

/**
 * this class controls the main flow of the taxi center.
 */
class MainFlow {
private:
    TaxiCenter taxiCenter;
    Map* map;
    void parseMap(int &width, int &height);
    void parseObstacles(std::vector<Point> &obstacles);
    void parseDriver(int &id, int &age, MeritalStatus &meritalStatus, int &yearsOfExp, int& cabID);
    void parseTaxi(int &id, int &cabKind, CarManufacturer &manufacturer, Color &color);
    //void parseStartingAndEndingPoints(Point &start, Point &end);
    //void parsePassengersNum(int &passengersNum);
    MeritalStatus parseMeritalStatus(char status);
    void parseTrip(int &id, Point &start, Point &end, int &passengersNum, double &tariff);
    CarManufacturer parseCarManufacturer(char manufacturer);
    Color parseColor(char color);
    void parseId(int &id);
    void validatePositiveNumber(int num);
    void validatePositiveNoneZeroNumber(int num);
    void validatePointInRangeOfMap(Point point);
public:
    MainFlow();
    ~MainFlow();
    void setWorldRepresentation();
    void addDriver();
    void addTaxi();
    void addTrip();
    //void attachTaxiToDriver();
    //void receiveCall();
    void printDriversLocation();
    void startDriving();
    TaxiCenter* getTaxiCenter();
    void setMap(Map* map);
};


#endif //TRANSPORTATION_MAINFLOW_H
