#include "MainFlow.h"
#include "boost/algorithm/string.hpp"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include <iostream>

/**
 * this function is a constructor of the main flow.
 */
MainFlow::MainFlow() {
    taxiCenter = TaxiCenter();
    map = NULL;
}

/**
 * this function is a destructor of the main flow.
 */
MainFlow::~MainFlow() {
    if (map != NULL)
        delete(map);
}

/**
 * this function ensure that the number 'num' is a positive number.
 * @param num - the number to check
 */
void MainFlow::validatePositiveNumber(int num) {
    if (num < 0)
        throw "not a positive input";
}

/**
 * this function ensure that the number 'num' is a positive and not zero number.
 * @param num - the number to check
 */
void MainFlow::validatePositiveNoneZeroNumber(int num) {
    if (num <= 0)
        throw "not a positive non zero input";
}

/**
 * this function ensure that the point 'point' is a valid point that is in the range of the map.
 * @param point - the point to check.
 */
void MainFlow::validatePointInRangeOfMap(Point point) {
    if (point.getX() >= map->getWidth() || point.getY() >= map->getHeight())
        throw "point coordinated are out of map range";
}

/**
 * this function parses the map from an input file.
 * @param width - the width of the map.
 * @param height - the height of the map.
 */
void MainFlow::parseMap(int &width, int &height) {
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
void MainFlow::parseObstacles(std::vector<Point> &obstacles) {
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
 * this function parses the merital status.
 * @param status - the char to parse.
 * @return - the merital status.
 */
MeritalStatus MainFlow::parseMeritalStatus(char status) {
    switch (status) {
        case 'D':
            return MeritalStatus::DIVORCED;
        case 'M':
            return MeritalStatus::MARRIED;
        case 'S':
            return MeritalStatus::SINGLE;
        case 'W':
            return MeritalStatus::WIDOWED;
        default:
            throw "invalid merital status inserted";
    }
}

/**
 * this function parses a line of input string splitted by ','.
 * @param arguments - vector of input strings
 */
void absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments) {
    std::string input;
    std::cin >> input;
    boost::split(arguments, input, boost::is_any_of(","), boost::token_compress_on);
}

/**
 * this function parses the input of the driver.
 * @param id - id of the driver
 * @param age - age of the driver
 * @param meritalStatus - merital status of the driver
 * @param yearsOfExp - years of experiance of the driver
 * @param cabID - cab id of the driver
 */
void MainFlow::parseDriver(int &id, int &age, MeritalStatus &meritalStatus, int &yearsOfExp, int& cabID) {
    std::vector<std::string> arguments;
    absorptionOfSeveralArgumentsInALine(arguments);
    if (arguments.size() != 5)
        throw "mismatch number of arguments for this operation";
    id = stoi(arguments[0]);
    validatePositiveNumber(id);
    age = stoi(arguments[1]);
    if (age <= 15)
        throw "invalid drier's age";
    validatePositiveNoneZeroNumber(age);
    meritalStatus = parseMeritalStatus(arguments[2][0]);
    yearsOfExp = stoi(arguments[3]);
    validatePositiveNumber(yearsOfExp);
    cabID = stoi(arguments[4]);
    validatePositiveNumber(cabID);
}

/**
 * this function parses the input of the trip.
 * @param id - id of the trip.
 * @param start - start point of the trip.
 * @param end - end point of the trip.
 * @param passengersNum - number of passengers of the trip.
 * @param tariff - tariff of the trip.
 */
void MainFlow::parseTrip(int &id, Point &start, Point &end, int &passengersNum, double &tariff) {
    std::vector<std::string> arguments;
    absorptionOfSeveralArgumentsInALine(arguments);
    if (arguments.size() != 7)
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
}

/**
 * this function parses the input of car manufacturer.
 * @param manufacturer - the manufacturer
 * @return - enum CarManufacturer
 */
CarManufacturer MainFlow::parseCarManufacturer(char manufacturer) {
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
Color MainFlow::parseColor(char color) {
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
void MainFlow::parseTaxi(int &id, int &cabKind, CarManufacturer &manufacturer, Color &color) {
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
/*
void MainFlow::parseStartingAndEndingPoints(Point &start, Point &end) {

}

void MainFlow::parsePassengersNum(int &passengersNum) {

}*/

/**
 * this function parses the input of the id.
 * @param id - the id
 */
void MainFlow::parseId(int &id) {
    std::cin >> id;
    validatePositiveNumber(id);
}

/**
 * this function sets the 'world' representation (height and width of the map and obstacles).
 */
void MainFlow::setWorldRepresentation() {
    int width, height;
    std::vector<Point> obstacles;
    parseMap(width, height);
    map = new Map(width, height);
    parseObstacles(obstacles);
    map->updateObstacles(obstacles);

    taxiCenter.setMap(map);
}

/**
 * this function add a driver to the main flow.
 */
void MainFlow::addDriver() {
    int id, age, yearsOfExp, cabID;
    MeritalStatus meritalStatus;
    parseDriver(id, age, meritalStatus, yearsOfExp, cabID);

    Driver* driver = new Driver(id, age, meritalStatus, yearsOfExp, map);
    try {
        taxiCenter.addDriver(driver);
    }
    catch (...) {
        delete(driver);
        throw;
    }
    taxiCenter.attachTaxiToDriver(driver, cabID);
}

/**
 * this function add a taxi to the main flow.
 */
void MainFlow::addTaxi() {
    int id, cabKind;
    CarManufacturer manufacturer;
    Color color;
    parseTaxi(id, cabKind, manufacturer, color);

    Cab * cab;
    if (cabKind == 1)
        cab = new StandardCab(id, 1, manufacturer, color, 1);
    else {
        if (cabKind == 2)
            cab = new LuxuryCab(id, 2, manufacturer, color, 2);
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
 * this function add a trip to the main flow.
 */
void MainFlow::addTrip() {
    int id, passengersNum;
    Point start, end;
    double tariff;
    parseTrip(id, start, end, passengersNum, tariff);

    taxiCenter.addTrip(id, start, end, passengersNum, tariff);
}
/*
void MainFlow::attachTaxiToDriver() {

}*/
/*
void MainFlow::receiveCall() {

}*/

/**
 * this function gets an id of driver and prints it's current location.
 */
void MainFlow::printDriversLocation() {
    int id;
    parseId(id);
    Point location = taxiCenter.getLocationOfDriver(id);
    std::cout << location;
}


/**
 * this function starts all the drivers.
 */
void MainFlow::startDriving() {
    taxiCenter.attachTripsToDrivers();
    taxiCenter.startAllDrivers();
}

/**
 * this function returns the taxi center member of main flow.
 * @return the taxi center.
 */
TaxiCenter* MainFlow::getTaxiCenter() {
    return &this->taxiCenter;
}

/**
 * this fnction returns the map member of main flow.
 * @param map the map.
 */
void MainFlow::setMap(Map* map) {
    this->map = map;
}