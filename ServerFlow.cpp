#include "ServerFlow.h"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include "Serialization.h"
#include "Tcp.h"
#include "easylogging++.h"
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//#pragma GCC diagnostic ignored "-Wno-deprecated-declarations"

/**
 * this function is a constructor of the serverflow.
 */
ServerFlow::ServerFlow() {
    //socket = s;
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
    for (int i = 0; i < size; i++)
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
/*

*/
/**
 * this function ensure that the number 'num' is a positive number.
 * @param num - the number to check
 *//*

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

*/
/**
 * this function ensure that the number 'num' is a positive and not zero number.
 * @param num - the number to check
 *//*

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
*/

/**
 * this function ensure that the point 'point' is a valid point that is in the range of the map.
 * @param point - the point to check.
 */
/*void ServerFlow::validatePointInRangeOfMap(int x, int y) {
    if (x >= map->getWidth() || y >= map->getHeight())
        throw "point coordinated are out of map range";
}*/

/**
 * this function parses the map from an input file.
 * @param width - the width of the map.
 * @param height - the height of the map.
 */
void ServerFlow::checkMapValidity(std::vector<std::string> &arguments) {
    /*validatePositiveNoneZeroNumber(width);
    validatePositiveNoneZeroNumber(height);*/

    std::string input;
    //std::string splitted;
    do {
        getline(cin, input);
        //boost::algorithm::trim(input);
        boost::split(arguments, input, boost::is_any_of(" "), boost::token_compress_on);
        if (arguments.size() != 2) {
            cout << "-1" << endl;
            continue;
        }
        if (!isNumber(arguments[0]) || !isNumber(arguments[1])) {
            cout << "-1" << endl;
            continue;
        }
        break;
    }while(true);
}

int ServerFlow::checkObstaclesNumValidity(int &numOfObstacles) {
    std::string input;
    do {
        getline(cin, input);
        cout << "inserted num " << endl;
        if (!isNumber(input))
            return 0;
        numOfObstacles = stoi(input);
        if(numOfObstacles < 0)
            return 0;
        return 1;
    }while(true);
}
/**
 * this function parses the obstacles from an input file.
 * @param obstacles - a vector of obstacles points.
 */
int ServerFlow::checkObstaclesValidity(std::vector<Point> &obstacles, int width, int height) {
    vector<string> obstaclesCoordinates;
    std::string input;
    int x, y;
    getline(cin, input);
    //boost::algorithm::trim(input);
    boost::split(obstaclesCoordinates, input, boost::is_any_of(","), boost::token_compress_on);
    cout << obstaclesCoordinates[0] <<endl;
    if (obstaclesCoordinates.size() != 2)
        return 0;
    if (!isNumber(obstaclesCoordinates[0]) || !isNumber(obstaclesCoordinates[1]))
        return 0;
    x = stoi(obstaclesCoordinates[0]);
    y = stoi(obstaclesCoordinates[1]);
    if ((x < 0) || (y < 0))
        return 0;
    //validate that the points are in the range of the map
    if(x >= width || y >= height)
        return 0;
    Point p(x, y);
    obstacles.push_back(p);
    return 1;
}


/**
 * this function parses a line of the trip input string splitted by ','.
 * @param arguments - vector of input strings
 */
bool ServerFlow::checkTripValidity(std::vector<std::string> &arguments) {
    std::string input;
    //bool error = false;
    getline(cin, input);
    //boost::algorithm::trim(input);
    boost::split(arguments, input, boost::is_any_of(","), boost::token_compress_on);
    if(arguments.size() != 8) {
        cout << "-1" << endl;
        return false;
    }
    if (!isNumber(arguments[0]) || !isNumber(arguments[1])
        || !isNumber(arguments[2]) || !isNumber(arguments[3])
        || !isNumber(arguments[4]) || !isNumber(arguments[5])
        || !isNumber(arguments[7])) {
        cout << "-1" << endl;
        return false;
    }
       /* if (arguments[0]<0 || arguments[1]<0 || arguments[2]<0 || arguments[3]<0 || arguments[4]<0 ||
                arguments[5]<0 || arguments[6]<0 || arguments[7]<=0) {
            cout << "-1" << endl;
            continue;
        }*/
    return true;
}

/**
 * this function parses a line of the taxi input string splitted by ','.
 * @param arguments - vector of input strings
 */
bool ServerFlow::checkTaxiValidity(std::vector<std::string> &arguments) {
    std::string input;
    getline(cin, input);
    //boost::algorithm::trim(input);
    boost::split(arguments, input, boost::is_any_of(","), boost::token_compress_on);
    if (arguments.size() != 4) {
        cout << "-1" << endl;
        return false;
    }
    if (!isNumber(arguments[0]) || !isNumber(arguments[1])
        || !isalpha((stoi(arguments[2]))) || !isalpha((stoi(arguments[3])))) {
        cout << "-1" << endl;
        return false;
    }
    return true;
}


/**
 * this function parses the input of the trip.
 * @param id - id of the trip.
 * @param start - start point of the trip.
 * @param end - end point of the trip.
 * @param passengersNum - number of passengers of the trip.
 * @param tariff - tariff of the trip.
 */
bool ServerFlow::parseTrip(int &id, Point &start, Point &end, int &passengersNum, double &tariff, int &startTime) {
    std::vector<std::string> arguments;
    int startX, startY, endX, endY;
    if(!checkTripValidity(arguments))
        return false;
    else{
        id = stoi(arguments[0]);
        startX = stoi(arguments[1]);
        startY = stoi(arguments[2]);
        endX = stoi(arguments[3]);
        endY = stoi(arguments[4]);
        passengersNum = stoi(arguments[5]);
        tariff = stod(arguments[6]);
        startTime = stoi(arguments[7]);
        if (id<0 || startX<0 || startY<0 || endX<0 || endY<0 || passengersNum<0 || tariff<0 || startTime<=0) {
            cout << "-1" << endl;
            return false;
        }
    }

    return true;
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
bool ServerFlow::parseTaxi(int &id, int &cabKind, CarManufacturer &manufacturer, Color &color) {
    std::vector<std::string> arguments;
    if (!checkTaxiValidity(arguments))
        return false;
    id = stoi(arguments[0]);
    cabKind = stoi(arguments[1]);
    if (id < 0 || !validateCabKind(cabKind)) {
        cout << "-1" << endl;
        return false;
    }
    try {
        manufacturer = parseCarManufacturer(arguments[2][0]);
    } catch  (...) {
        cout << "-1" << endl;
        return false;
    }
    try {
        color = parseColor(arguments[3][0]);
    } catch  (...) {
        cout << "-1" << endl;
        return false;
    }
    return true;
}

/**
 * this function parses the input of the id.
 * @param id - the id
 */
/*void ServerFlow::parseId(int &id) {
	do {
		std::cin.clear();
		std::cin >> id;
        if(std::cin.fail() && EINTR == errno) {
            cout << "-1" << endl;
            continue;
        }
        if(id < 0) {
            cout << "-1" << endl;
            continue;
        }
        break;

	} while (true);
}*/

/**
 * this function sets the 'world' representation (height and width of the map and obstacles).
 */
void ServerFlow::setWorldRepresentation() {
    int width, height, numOfObstacles;
    std::vector<Point> obstacles;
    std::vector<std::string> arguments;
    bool isValidObstacle;

    //check if the map and obstacles are valid, if not than re-scan them.
    do {
        isValidObstacle = false;
        checkMapValidity(arguments);
        width = stoi(arguments[0]);
        height = stoi(arguments[1]);
        cout << "inserted map " << endl;
        if (width < 0 || height < 0) {
            cout << "-1" << endl;
            continue;
        }
        if(!checkObstaclesNumValidity(numOfObstacles)) {
            cout << "-1" << endl;
            continue;
        }
        for(int i = 0; i < numOfObstacles; i++) {
            if(checkObstaclesValidity(obstacles, width, height))
                continue;
            else {
                cout << "-1" << endl;
                isValidObstacle = true;
                break;
            }
        }
        if(isValidObstacle)
            continue;
        break;
    }while(true);

    map = new Map(width, height);
    map->updateObstacles(obstacles);
    taxiCenter->setMap(map);
}

/**
 * this function add drivers to the serverflow and attaches them with cabs.
 */
void ServerFlow::addDrivers() {
    int numOfDrivers;
    std::string input;
    getline(cin, input);
    if (!isNumber(input)) {
        cout << "-1" << endl;
        return;
    }
    numOfDrivers = stoi(input);
    if(numOfDrivers <= 0) {
        cout << "-1" << endl;
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

/**
 * this function checks if the number of the cabkind is a valid option (1/2)
 * @param num - the number to check
 * @return - the number representing the answer(0 = invalid)
 */
int ServerFlow::validateCabKind(int num) {
    if ((num != 1) && (num != 2))
        return 0;
    return 1;
}

/**
 * this function add a taxi to the serverflow.
 */
void ServerFlow::addTaxi() {
    int id, cabKind;
    CarManufacturer manufacturer;
    Color color;
    if (!parseTaxi(id, cabKind, manufacturer, color))
        return;
    //validateCabKind(cabKind);
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
    //if there was an error, back to the menu.
    if(!parseTrip(id, start, end, passengersNum, tariff, startTime))
        return;
    taxiCenter->addTrip(id, start, end, passengersNum, tariff, startTime);
}

/**
 * this function gets an id of driver and prints it's current location.
 */
void ServerFlow::printDriversLocation() {
    int id;
    std::string input;
    getline(cin, input);
    if (!isNumber(input)) {
        cout << "-1" << endl;
        return;
    }
    id = stoi(input);
    if(id < 0) {
        cout << "-1" << endl;
        return;
    }
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

/**
 * this function sets the socket member of the serverFlow.
 * @param s = the new socket.
 */
void ServerFlow::setSocket(Socket* s) {
    this->socket = s;
}

/**
 * this function checks if a given string is a number.
 * @param s - the string
 * @return - return the answer
 */
bool ServerFlow::isNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
