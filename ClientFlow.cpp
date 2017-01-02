#include "ClientFlow.h"
#include "boost/algorithm/string.hpp"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include <iostream>
#include "Serialization.h"

/**
 * this function is a constructor of the main flow.
 */
ClientFlow::ClientFlow(Socket* s) {
    socket = s;
    map = NULL;
    driver = NULL;
}

/**
 * this function is a destructor of the main flow.
 */
ClientFlow::~ClientFlow() {
    if (map != NULL)
        delete(map);
}

/**
 * this function ensure that the number 'num' is a positive number.
 * @param num - the number to check
 */
void ClientFlow::validatePositiveNumber(int num) {
    if (num < 0)
        throw "not a positive input";
}

/**
 * this function ensure that the number 'num' is a positive and not zero number.
 * @param num - the number to check
 */
void ClientFlow::validatePositiveNoneZeroNumber(int num) {
    if (num <= 0)
        throw "not a positive non zero input";
}

/**
 * this function parses the merital status.
 * @param status - the char to parse.
 * @return - the merital status.
 */
MeritalStatus ClientFlow::parseMeritalStatus(char status) {
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
void ClientFlow::absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments) {
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
void ClientFlow::parseDriver(int &id, int &age, MeritalStatus &meritalStatus, int &yearsOfExp, int& cabID) {
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
 * this function parses the input of the id.
 * @param id - the id
 */
void ClientFlow::parseId(int &id) {
    std::cin >> id;
    validatePositiveNumber(id);
}

/**
 * this function add a driver to the main flow.
 */
void ClientFlow::addDriver() {
    int id, age, yearsOfExp, cabID;
    MeritalStatus meritalStatus;
    parseDriver(id, age, meritalStatus, yearsOfExp, cabID);

    driver = new Driver(id, age, meritalStatus, yearsOfExp, cabID);
    std::string serialized = serialize<Driver>(driver);
    socket->sendData(serialized);
    char buffer[10240];
    socket->receiveData(buffer, sizeof(buffer));
    Cab *cab = deserialize<Cab>(buffer, sizeof(buffer));
    driver->attachCab(cab);

    //initialize, recieve data, driver.serialize, txicenter.add driver, add cab and send it
}

/**
 * this fnction returns the map member of main flow.
 * @param map the map.
 */
void ClientFlow::setMap(Map* map) {
    this->map = map;
}

void ClientFlow::flow() {
    char buffer[10240];
    socket->receiveData(buffer, sizeof(buffer));
    Trip *trip = deserialize<Trip>(buffer, sizeof(buffer));
    driver->updateTrip(trip);

    while(1) {
        memset(buffer, '0', sizeof(buffer));
        socket->receiveData(buffer, sizeof(buffer));
        if (buffer == "go")
            driver->move();
    }
}