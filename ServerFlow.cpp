#include "ServerFlow.h"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include "Serialization.h"
#include "Tcp.h"
#include "easylogging++.h"

/**
 * this function is a constructor of the serverflow.
 */
ServerFlow::ServerFlow(Socket* s) {
    socket = s;
    taxiCenter = new TaxiCenter();
    map = NULL;
    pthread_mutex_init(&clientHandleMessagesLock, NULL);
    pthread_mutex_init(&taxiCenterLock, NULL);
    pthread_mutex_init(&driversToClientHandlesMapLock, NULL);
    pthread_mutex_init(&serializationLock, NULL);
}

/**
 * this function is a destructor of the serverflow.
 */
ServerFlow::~ServerFlow() {
    int size = clientsHandles.size();
    for (int i=0; i<size; i++)
        delete  clientsHandles[i];
    pthread_mutex_destroy(&serializationLock);
    pthread_mutex_destroy(&driversToClientHandlesMapLock);
    pthread_mutex_destroy(&taxiCenterLock);
    pthread_mutex_destroy(&clientHandleMessagesLock);

    delete taxiCenter;

    if (this->map != NULL)
        delete(this->map);

    delete(this->socket);
}

/**
 * this function ensure that the number 'num' is a positive number.
 * @param num - the number to check
 */
void ServerFlow::validatePositiveNumber(int num) {
    do {
        std::cin >> num;
        if(std::cin.fail() && EINTR == errno) {
            cout << "-1" << endl;
            continue;
        }
        else  {
            if (num < 0) {
                cout << "-1" << endl;
                continue;
            }
            break;
        }
    } while (true);

}

/**
 * this function ensure that the number 'num' is a positive and not zero number.
 * @param num - the number to check
 */
void ServerFlow::validatePositiveNoneZeroNumber(int num) {

    do {
        std::cin >> num;
        if(std::cin.fail() && EINTR == errno) {
            cout << "-1" << endl;
            continue;
        }
        else  {
            if (num <= 0) {
                cout << "-1" << endl;
                continue;
            }
            break;
        }
    } while (true);
}

/**
 * this function ensure that the point 'point' is a valid point that is in the range of the map.
 * @param point - the point to check.
 */
void ServerFlow::validatePointInRangeOfMap(int x, int y) {
    if (x >= map->getWidth() || y>= map->getHeight())
        throw "point coordinated are out of map range";
}

/**
 * this function parses the map from an input file.
 * @param width - the width of the map.
 * @param height - the height of the map.
 */
void ServerFlow::parseMap(int &width, int &height) {
    validatePositiveNoneZeroNumber(width);
    validatePositiveNoneZeroNumber(height);
}

/**
 * this function parses the obstacles from an input file.
 * @param obstacles - a vector of obstacles points.
 */
void ServerFlow::parseObstacles(std::vector<Point> &obstacles) {
    int numOfObstacles;
    validatePositiveNoneZeroNumber(numOfObstacles);
    std::string obstaclesCoordinates;
    for (int i=0; i<numOfObstacles; i++) {
    int x,y;
		do {
			std::cin.clear();
			std::cin >> obstaclesCoordinates;
            if(std::cin.fail() && EINTR == errno)
                continue;
            std::size_t indexOfComma = obstaclesCoordinates.find(',');
            if (indexOfComma == std::string::npos)
               // throw "not a valid representation of point";
                continue;
            x = stoi(obstaclesCoordinates.substr(0, indexOfComma));
            y = stoi(obstaclesCoordinates.substr(indexOfComma+1));
            if((x < 0) || (y < 0))
                continue;
            try {
                validatePointInRangeOfMap(x, y);
            }
            catch (...) {
                continue;
            }
            break;
		} while (true);

        Point p(x, y);
        obstacles.push_back(p);
    }
}

//****************here**********************
/**
 * this function parses a line of input string splitted by ','.
 * @param arguments - vector of input strings
 */
void ServerFlow::absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments) {
    std::string input;

	do {
		std::cin.clear();
		std::cin >> input;
	} while (std::cin.fail() && EINTR == errno);

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
    validatePositiveNumber(tariff);
    startTime = stoi(arguments[7]);
    validatePositiveNoneZeroNumber(startTime);
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
    validateCabKind(cabKind);
    manufacturer = parseCarManufacturer(arguments[2][0]);
    color = parseColor(arguments[3][0]);
}
}

/**
 * this function parses the input of the id.
 * @param id - the id
 */
void ServerFlow::parseId(int &id) {
	do {
		std::cin.clear();
		std::cin >> id;
	} while (std::cin.fail() && EINTR == errno);

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

    taxiCenter->setMap(map);
}

/**
 * this function add drivers to the serverflow and attaches them with cabs.
 */
void ServerFlow::addDrivers() {
    int numOfDrivers;
	do {
		std::cin.clear();
		std::cin >> numOfDrivers;
	} while (std::cin.fail() && EINTR == errno);

    if (std::cin.fail())
        throw "not a number";
    validatePositiveNumber(numOfDrivers);
	if (numOfDrivers == 0) {
		return;
	}

    Tcp* tcpSocket = static_cast<Tcp*>(socket);
	if (tcpSocket == NULL) {
		perror("error casting to tcp socket");
	}

    LOG(DEBUG) << "size before " << clientHandlesMessages.size() << "\n";
	clientHandlesMessages.resize(clientHandlesMessages.size() + numOfDrivers);
    LOG(DEBUG) << "size after " << clientHandlesMessages.size() << "\n";

    for (int i = 0; i < numOfDrivers; i++) {

        int newSocketDescriptor = tcpSocket->acceptClient();
        Tcp* newTcpSocket = new Tcp(*tcpSocket);
        newTcpSocket->setSocketDescriptor(newSocketDescriptor);

        ClientHandleThread* clientHandleThread = new ClientHandleThread(clientsHandles.size(), &clientHandleMessagesLock, &taxiCenterLock,
                                              &driversToClientHandlesMapLock, &serializationLock, newTcpSocket,
                                              &driversIdToClientHandlesIdMap, &clientHandlesMessages,
                                              taxiCenter);
        clientHandleThread->start();
        clientsHandles.push_back(clientHandleThread);
    }
}

void ServerFlow::validateCabKind(int num) {
    if ((num != 1) && (num != 2))
        throw "invalid cab kind number";
}

/**
 * this function add a taxi to the serverflow.
 */
void ServerFlow::addTaxi() {
    int id, cabKind;
    CarManufacturer manufacturer;
    Color color;
    parseTaxi(id, cabKind, manufacturer, color);
    validateCabKind(cabKind);
    Cab * cab;
    if (cabKind == 1)
        cab = new Cab(id, 1, manufacturer, color, 1);
    else if (cabKind == 2)
        cab = new Cab(id, 2, manufacturer, color, 2);

    try {
        taxiCenter->addTaxi(cab);
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

    taxiCenter->addTrip(id, start, end, passengersNum, tariff, startTime);
}

/**
 * this function gets an id of driver and prints it's current location.
 */
void ServerFlow::printDriversLocation() {
    int id;
    parseId(id);
    pthread_mutex_lock(&taxiCenterLock);
    Point location = taxiCenter->getLocationOfDriver(id);
    pthread_mutex_unlock(&taxiCenterLock);
    std::cout << location;
}

/**
 * this function returns the taxi center member of serverflow.
 * @return the taxi center.
 */
TaxiCenter* ServerFlow::getTaxiCenter() {
    return this->taxiCenter;
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
    pthread_mutex_lock(&taxiCenterLock);
    //attach trips to drivers when it's trip time
    taxiCenter->updateTime();

    std::vector<Driver *> drivers = taxiCenter->getDrivers();

    std::vector<Driver *> attachedTripsDrivers = taxiCenter->attachTripsToDrivers();
    pthread_mutex_unlock(&taxiCenterLock);


    for (int i = 0; i < drivers.size(); i++) {
        vector<Driver *>::iterator driversIndex = std::find(attachedTripsDrivers.begin(), attachedTripsDrivers.end(),
                                                            drivers[i]);
        pthread_mutex_lock(&driversToClientHandlesMapLock);
        int clientHandleId = driversIdToClientHandlesIdMap.find(drivers[i]->getID())->second;
        pthread_mutex_unlock(&driversToClientHandlesMapLock);
        if (driversIndex != attachedTripsDrivers.end()) {
            Trip *trip = drivers[i]->getTrip();

            LOG(DEBUG) << "id is " << trip->getID() << "\n";
            LOG(DEBUG) <<  "startP is " << trip->getStartP();
            LOG(DEBUG) <<  "endP is " << trip->getEndP();
            LOG(DEBUG) << "passengers are " << trip->getPassengersNum() << "\n";
            LOG(DEBUG) << "tariff is " << trip->getTariff() << "\n";
            LOG(DEBUG) << "road is %p" << trip->getRoad() << "\n";
            LOG(DEBUG) << "currentLocation is " << trip->getCurrentLocation() << "\n";
            LOG(DEBUG) << "startTime is " <<trip->getStartTime() << "\n";
     
            pthread_mutex_lock(&serializationLock);
            std::string serialized = serialize<Trip>(trip);
            pthread_mutex_unlock(&serializationLock);

            pthread_mutex_lock(&clientHandleMessagesLock);
            clientHandlesMessages[clientHandleId].push_back(serialized);
            pthread_mutex_unlock(&clientHandleMessagesLock);
			
			clientsHandles[clientHandleId]->notify();
        }
        else {
            if (drivers[i]->getTrip() != NULL) {
                pthread_mutex_lock(&clientHandleMessagesLock);
                clientHandlesMessages[clientHandleId].push_back("go");
                pthread_mutex_unlock(&clientHandleMessagesLock);

				clientsHandles[clientHandleId]->notify();

                drivers[i]->move();
            }
        }
    }
}

/**
 * this function sends "exit" messages to all the clients.
 */
void ServerFlow::exitSignal() {
    for (int i=0; i<clientHandlesMessages.size(); i++) {
        pthread_mutex_lock(&clientHandleMessagesLock);
        clientHandlesMessages[i].push_back("exit");
        pthread_mutex_unlock(&clientHandleMessagesLock);
		clientsHandles[i]->notify();
        clientsHandles[i]->join();
    }
    //pthread_exit(NULL);
}
