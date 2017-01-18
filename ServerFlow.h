
#ifndef TRANSPORTATION_SERVERFLOW_H
#define TRANSPORTATION_SERVERFLOW_H

#include "TaxiCenter.h"
#include "Cab.h"
#include "Driver.h"
#include "Point.h"
#include "CarManufacturer.h"
#include "Color.h"
#include "MeritalStatus.h"
#include "Socket.h"
#include "ClientHandleThread.h"

/**
 * this class controls the ServerFlow.
 */
class ServerFlow {
private:
    Socket* socket;
    TaxiCenter taxiCenter;
    Map* map;
    pthread_mutex_t lock;
    vector<ClientHandleThread> clientsHandles;
    std::map<int, int> driversIdToClientHandlesIdMap;
    std::vector<std::string> clientHandlesMessages;
    void parseMap(int &width, int &height);
    void parseObstacles(std::vector<Point> &obstacles);
    void parseTaxi(int &id, int &cabKind, CarManufacturer &manufacturer, Color &color);
    //void parseStartingAndEndingPoints(Point &start, Point &end);
    //void parsePassengersNum(int &passengersNum);
    void parseTrip(int &id, Point &start, Point &end, int &passengersNum, double &tariff, int &startTime);
    CarManufacturer parseCarManufacturer(char manufacturer);
    Color parseColor(char color);
    void parseId(int &id);
    void validatePositiveNumber(int num);
    void validatePositiveNoneZeroNumber(int num);
    void validatePointInRangeOfMap(Point point);
    void absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments);
public:
    ServerFlow(Socket * s);
    ~ServerFlow();
    void setWorldRepresentation();
    void addTaxi();
    void addTrip();
    //void attachTaxiToDriver();
    //void receiveCall();
    void printDriversLocation();
   // void moveAllOneStep();
    TaxiCenter* getTaxiCenter();
    void setMap(Map* map);
    void addDrivers();
    void updateTime();
    void exitSignal();
};

#endif //TRANSPORTATION_SERVERFLOW_H