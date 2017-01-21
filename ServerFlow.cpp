#include "ServerFlow.h"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include "Serialization.h"
#include "Tcp.h"

/**
 * this function is a constructor of the serverflow.
 */
ServerFlow::ServerFlow(Socket* s) {
    socket = s;
    taxiCenter = TaxiCenter();
    map = NULL;
    pthread_mutex_init(&lock, NULL);
}

/**
 * this function is a destructor of the serverflow.
 */
ServerFlow::~ServerFlow() {
    pthread_mutex_destroy(&lock);

    if (this->map != NULL)
        delete(this->map);

    delete(this->socket);
}

/**
 * this function ensure that the number 'num' is a positive number.
 * @param num - the number to check
 */
void ServerFlow::validatePositiveNumber(int num) {
    if (num < 0)
        throw "not a positive input";
}

/**
 * this function ensure that the number 'num' is a positive and not zero number.
 * @param num - the number to check
 */
void ServerFlow::validatePositiveNoneZeroNumber(int num) {
    if (num <= 0)
        throw "not a positive non zero input";
}

/**
 * this function ensure that the point 'point' is a valid point that is in the range of the map.
 * @param point - the point to check.
 */
void ServerFlow::validatePointInRangeOfMap(Point point) {
    if (point.getX() >= map->getWidth() || point.getY() >= map->getHeight())
        throw "point coordinated are out of map range";
}

/**
 * this function parses the map from an input file.
 * @param width - the width of the map.
 * @param height - the height of the map.
 */
void ServerFlow::parseMap(int &width, int &height) {
    std::cin >> width >> height;
    if (std::cin.fail())
        throw "not a number";
    validatePositiveNoneZeroNumber(width);
    validatePositiveNoneZeroNumber(height);
}

/**
 * this function parses the obstacles from an input file.
 * @param obstacles - a vector of obstacles points.
 */
void ServerFlow::parseObstacles(std::vector<Point> &obstacles) {
    int numOfObstacles;
    std::cin >> numOfObstacles;
    if (std::cin.fail())
        throw "not a number";
    validatePositiveNumber(numOfObstacles);
    if (numOfObstacles == 0)
        return;
    std::string obstaclesCoordinates;
    for (int i=0; i<numOfObstacles; i++) {
        std::cin >> obstaclesCoordinates;
        if (std::cin.fail())
            throw "invalid argument";
        std::size_t indexOfComma = obstaclesCoordinates.find(',');
        if (indexOfComma == std::string::npos)
            throw "not a valid representation of point";
        int x = stoi(obstaclesCoordinates.substr(0, indexOfComma));
        int y = stoi(obstaclesCoordinates.substr(indexOfComma+1));
        validatePositiveNumber(x);
        validatePositiveNumber(y);
        Point p(x, y);
        validatePointInRangeOfMap(p);
        obstacles.push_back(p);
    }
}

/**
 * this function parses a line of input string splitted by ','.
 * @param arguments - vector of input strings
 */
void ServerFlow::absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments) {
    std::string input;
    std::cin >> input;
    boost::split(arguments, input, boost::is_any_of(","), boost::token_compress_on);
}

/**
 * this function parses the input of the trip.
 * @param id - id of the trip.
 * @param start - start point of the trip.
 * @param end - end point of the trip.
 * @param passengersNum - number of passengers of the trip.
 * @param tariff - tariff of the trip.
 */
void ServerFlow::parseTrip(int &id, Point &start, Point &end, int &passengersNum, double &tariff, int &startTime) {
    std::vector<std::string> arguments;
    absorptionOfSeveralArgumentsInALine(arguments);
    if (arguments.size() != 8)
        throw "mismatch number of arguments for this operation";
    id = stoi(arguments[0]);
    validatePositiveNumber(id);
    int startX = stoi(arguments[1]);
    int startY = stoi(arguments[2]);
    validatePositiveNumber(startX);
    validatePositiveNumber(startY);
    start = Point(startX, startY);
    validatePointInRangeOfMap(start);
    int endX = stoi(arguments[3]);
    int endY = stoi(arguments[4]);
    validatePositiveNumber(endX);
    validatePositiveNumber(endY);
    end = Point(endX, endY);
    validatePointInRangeOfMap(end);
    passengersNum = stoi(arguments[5]);
    validatePositiveNoneZeroNumber(passengersNum);
    if(passengersNum > 5)
        throw "passengers number exceeds car's capacity";
    tariff = stod(arguments[6]);
    validatePositiveNoneZeroNumber(tariff);
    startTime = stoi(arguments[7]);
    validatePositiveNumber(startTime);
}

/**
 * this function parses the input of car manufacturer.
 * @param manufacturer - the manufacturer
 * @return - enum CarManufacturer
 */
CarManufacturer ServerFlow::parseCarManufacturer(char manufacturer) {
    switch (manufacturer) {
        case 'F':
            return CarManufacturer::FIAT;
        case 'H':
            return CarManufacturer::HONDA;
        case 'S':
            return CarManufacturer::SUBARO;
        case 'T':
            return CarManufacturer::TESLA;
        default:
            throw "invalid car manufacturer inserted";
    }
}

/**
 * this function parses the input of the color.
 * @param color - the color.
 * @return - enum Color.
 */
Color ServerFlow::parseColor(char color) {
    switch (color) {
        case 'B':
            return Color::BLUE;
        case 'G':
            return Color::GREEN;
        case 'P':
            return Color::PINK;
        case 'R':
            return Color::RED;
        case 'W':
            return Color::WHITE;
        default:
            throw "invalid color inserted";
    }
}

/**
 * this function parses the input of the taxi.
 * @param id - id of the taxi.
 * @param cabKind - the cab kind of the taxi.
 * @param manufacturer - the car manufacturer of the taxi.
 * @param color - the color of the taxi.
 */
void ServerFlow::parseTaxi(int &id, int &cabKind, CarManufacturer &manufacturer, Color &color) {
    std::vector<std::string> arguments;
    absorptionOfSeveralArgumentsInALine(arguments);
    if (arguments.size() != 4)
        throw "mismatch number of arguments for this operation";
    id = stoi(arguments[0]);
    validatePositiveNumber(id);
    cabKind = stoi(arguments[1]);
    manufacturer = parseCarManufacturer(arguments[2][0]);
    color = parseColor(arguments[3][0]);
}


/**
 * this function parses the input of the id.
 * @param id - the id
 */
void ServerFlow::parseId(int &id) {
    std::cin >> id;
    validatePositiveNumber(id);
}

/**
 * this function sets the 'world' representation (height and width of the map and obstacles).
 */
void ServerFlow::setWorldRepresentation() {
    int width, height;
    std::vector<Point> obstacles;
    parseMap(width, height);
    map = new Map(width, height);
    parseObstacles(obstacles);
    map->updateObstacles(obstacles);

    taxiCenter.setMap(map);
}

/**
 * this function add drivers to the serverflow and attaches them with cabs.
 */
void ServerFlow::addDrivers() {
    int numOfDrivers;
    std::cin >> numOfDrivers;
    if (std::cin.fail())
        throw "not a number";
    validatePositiveNumber(numOfDrivers);
    if (numOfDrivers == 0)
        return;
    //char buffer[10240];

    Tcp* tcpSocket = static_cast<Tcp*>(socket);
    if (tcpSocket != NULL)
        // do something
    //tcpSocket->setListenToConnections();

    for (int i = 0; i < numOfDrivers; i++) {

        int newSocketDescriptor = tcpSocket->acceptClient();
        //Tcp* newTcpSocket = new Tcp(newSocketDescriptor, tcpSocket->pr, tcpSocket->this_addr.sin_port);
        Tcp* newTcpSocket = new Tcp(*tcpSocket);
        newTcpSocket->setSocketDescriptor(newSocketDescriptor);

        clientHandlesMessages.push_back("");
        ClientHandleThread clientHandleThread(i, &lock, newTcpSocket,
                                              driversIdToClientHandlesIdMap, clientHandlesMessages,
                                              taxiCenter);
        clientHandleThread.start();
        //clientsHandles.push_back(clientHandleThread);
        /*memset(buffer, '0', sizeof(buffer));
        socket->receiveData(buffer, sizeof(buffer));
        Driver *driver = deserialize<Driver>(buffer, sizeof(buffer));
        try {
            taxiCenter.addDriver(driver);
        }
        catch (...) {
            delete(driver);
            throw;
        }
        Cab* cab = taxiCenter.attachTaxiToDriver(driver, driver->getCabID());
        std::string serialized = serialize<Cab>(cab);
        socket->sendData(serialized);*/
    }
}


/**
 * this function add a taxi to the serverflow.
 */
void ServerFlow::addTaxi() {
    int id, cabKind;
    CarManufacturer manufacturer;
    Color color;
    parseTaxi(id, cabKind, manufacturer, color);

    Cab * cab;
    if (cabKind == 1)
        cab = new Cab(id, 1, manufacturer, color, 1);
    else {
        if (cabKind == 2)
            cab = new Cab(id, 2, manufacturer, color, 2);
        else
            throw "invalid cab kind number";
    }

    try {
        taxiCenter.addTaxi(cab);
    }
    catch (...) {
        delete(cab);
        throw;
    }
}

/**
 * this function add a trip to the serverflow.
 */
void ServerFlow::addTrip() {
    int id, passengersNum, startTime;
    Point start, end;
    double tariff;
    parseTrip(id, start, end, passengersNum, tariff, startTime);

    taxiCenter.addTrip(id, start, end, passengersNum, tariff, startTime);
}

/**
 * this function gets an id of driver and prints it's current location.
 */
void ServerFlow::printDriversLocation() {
    int id;
    parseId(id);
    Point location = taxiCenter.getLocationOfDriver(id);
    std::cout << location;
}


/**
 * this function starts all the drivers.
 */
/*void ServerFlow::moveAllOneStep() {
   // taxiCenter.attachTripsToDrivers();

    //movew the drivers of the trips in this current time
    taxiCenter.moveOneStepAllDrivers();
}*/

/**
 * this function returns the taxi center member of serverflow.
 * @return the taxi center.
 */
TaxiCenter* ServerFlow::getTaxiCenter() {
    return &this->taxiCenter;
}

/**
 * this fnction returns the map member of serverflow.
 * @param map the map.
 */
void ServerFlow::setMap(Map* map) {
    this->map = map;
}

/**
 * this function updates the time of the world now, attaches trip to drivers in which the time
 * is now, and move one step all the drivers.
 */
void ServerFlow::updateTime() {
    //attach trips to drivers when it's trip time
    taxiCenter.updateTime();

    std::vector<Driver *> drivers = taxiCenter.getDrivers();

    std::vector<Driver *> attachedTripsDrivers = taxiCenter.attachTripsToDrivers();
    //for (int i = 0; i < attachedTripsDrivers.size(); i++) {

    for (int i = 0; i < drivers.size(); i++) {
        vector<Driver *>::iterator driversIndex = std::find(attachedTripsDrivers.begin(), attachedTripsDrivers.end(),
                                                            drivers[i]);
        int clientHandleId = driversIdToClientHandlesIdMap.find(attachedTripsDrivers[i]->getID())->second;
        if (driversIndex != attachedTripsDrivers.end()) {
            Trip *trip = attachedTripsDrivers[i]->getTrip();
            std::string serialized = serialize<Trip>(trip);

            pthread_mutex_lock(&lock);
            clientHandlesMessages[clientHandleId] = serialized;
            pthread_mutex_unlock(&lock);
            //socket->sendData(serialized);
        }
            //send 'go'
        else {
            if (drivers[i]->getTrip() != NULL) {
                pthread_mutex_lock(&lock);
                clientHandlesMessages[clientHandleId] = "go";
                pthread_mutex_unlock(&lock);

                drivers[i]->move();
            }
        }
    }

    //send 'go'
    /*if (attachedTripsDrivers.size() == 0) {
        std::vector<Driver*> drivers = taxiCenter.getDrivers();
        for (int i = 0; i < drivers.size(); i++) {
            socket->sendData("go");
            drivers[i]->move();
        }
    }*/
}
void ServerFlow::exitSignal() {
    for (int i=0; i<clientHandlesMessages.size(); i++) {
        pthread_mutex_lock(&lock);
        clientHandlesMessages[i] = "exit";
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}