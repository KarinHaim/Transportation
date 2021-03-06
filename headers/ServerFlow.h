
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
    Socket* guiClient;
    TaxiCenter* taxiCenter;
    Map map;
    pthread_mutex_t clientHandleMessagesLock;
    pthread_mutex_t taxiCenterLock;
    pthread_mutex_t driversToClientHandlesMapLock;
    pthread_mutex_t serializationLock;
    vector<ClientHandleThread*> clientsHandles;
    std::map<int, int> driversIdToClientHandlesIdMap;
    std::vector<std::deque<std::string>> clientHandlesMessages;
    void checkMapValidity(std::vector<std::string> &arguments);
    int checkObstaclesValidity(std::vector<Point> &obstacles, int width, int height);
    bool parseTaxi(int &id, int &cabKind, CarManufacturer &manufacturer, Color &color);
    bool parseTrip(int &id, Point &start, Point &end, int &passengersNum, double &tariff, int &startTime);
    CarManufacturer parseCarManufacturer(char manufacturer);
    Color parseColor(char color);
    int validateCabKind(int num);
    bool checkTripValidity(std::vector<std::string> &arguments);
    bool checkTaxiValidity(std::vector<std::string> &arguments);
    int checkObstaclesNumValidity(int &numOfObstacles);
public:
    ServerFlow();
    ~ServerFlow();
    void setWorldRepresentation();
    void addTaxi();
    void addTrip();
    void printDriversLocation();
    TaxiCenter* getTaxiCenter();
    void setMap(Map map);
    void addDrivers();
    void updateTime();
    void exitSignal();
    void setSocket(Socket* s);
    void acceptGuiClient();
    void flow();
};
bool isNumber(const std::string &s);

#endif //TRANSPORTATION_SERVERFLOW_H
