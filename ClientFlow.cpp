#include "ClientFlow.h"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include "Serialization.h"

/**
 * this function is a constructor of the main flow.
 */
ClientFlow::ClientFlow() {
    //socket = s;
    driver = NULL;
}

/**
 * this function is a destructor of the main flow.
 */
ClientFlow::~ClientFlow() {
    delete(this->driver);
    delete(this->socket);
}

/**
 * this function ensure that the number 'num' is a positive number.
 * if the input is invalid, exit the program on the client side.
 * @param num - the number to check
 *//*

void ClientFlow::validatePositiveNumber(int num) {
    if (num < 0)
        exit(1);
}

*/
/**
 * this function ensure that the number 'num' is a positive and not zero number.
 * if the input is invalid, exit the program on the client side.
 * @param num - the number to check
 *//*

void ClientFlow::validatePositiveNoneZeroNumber(int num) {
    if (num <= 0)
        exit(1);
}
*/

/**
 * this function parses the merital status.
 * if the input is invalid, exit the program on the client side.
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
            exit(1);
    }
}

/**
 * this function parses a line of input string splitted by ','.
 * if the input is invalid, exit the program on the client side.
 * @param arguments - vector of input strings
 */
void ClientFlow::absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments) {
    std::string input;
    //bool error = false;
    getline(cin, input);
    boost::algorithm::trim(input);
    //boost::algorithm::trim(input);
    boost::split(arguments, input, boost::is_any_of(","), boost::token_compress_on);
    if(arguments.size() != 5)
        exit(1);
    if (!isNumber(arguments[0]) || !isNumber(arguments[1])
        || !isalpha(stoi(arguments[2])) || !isNumber(arguments[3])
        || !isNumber(arguments[4]))
        exit(1);

    boost::split(arguments, input, boost::is_any_of(","), boost::token_compress_on);
}

/**
 * this function parses the input of the driver.
 * if the input is invalid, exit the program on the client side.
 * @param id - id of the driver
 * @param age - age of the driver
 * @param meritalStatus - merital status of the driver
 * @param yearsOfExp - years of experiance of the driver
 * @param cabID - cab id of the driver
 */
void ClientFlow::parseDriver(int &id, int &age, MeritalStatus &meritalStatus, int &yearsOfExp, int& cabID) {
    std::vector<std::string> arguments;
    absorptionOfSeveralArgumentsInALine(arguments);
    id = stoi(arguments[0]);
    age = stoi(arguments[1]);
    meritalStatus = parseMeritalStatus(arguments[2][0]);
    yearsOfExp = stoi(arguments[3]);
    cabID = stoi(arguments[4]);
    if (id < 0 || age < 0 || yearsOfExp < 0 || cabID < 0)
        exit(1);
}

/**
 * this function parses the input of the id.
 * @param id - the id
 */
//void ClientFlow::parseId(int &id) {
//    std::cin >> id;
//    validatePositiveNumber(id);
//}

/**
 * this function scan a new driver and validate the input.
 * @return the driver.
 */
Driver* ClientFlow::scanDriver() {
    int id, age, yearsOfExp, cabID;
    MeritalStatus meritalStatus;
    parseDriver(id, age, meritalStatus, yearsOfExp, cabID);
    driver = new Driver(id, age, meritalStatus, yearsOfExp, cabID);
    return driver;
}

/**
 * this function add a driver via the socket.
 * @param driver - the driver to send.
 */
void ClientFlow::addDriver(Driver* driver) {
    std::string serialized = serialize<Driver>(driver);
    socket->sendData(serialized);
    char buffer[40000];
    socket->receiveData(buffer, sizeof(buffer));
    Cab *cab = deserialize<Cab>(buffer, sizeof(buffer));
    driver->attachCab(cab);
}
/**
 * this function take care of the flow between the client and the derver.
 */
void ClientFlow::flow() {
    char buffer[40000];

    socket->receiveData(buffer, sizeof(buffer));
    while (strcmp(buffer, "exit") != 0) {
        if (strcmp(buffer, "go") == 0)
            driver->move();
        else {
            Trip *trip = deserialize<Trip>(buffer, sizeof(buffer));
            driver->updateTrip(trip);
        }
        memset(buffer, 0, sizeof(buffer));
        socket->receiveData(buffer, sizeof(buffer));
    }
}

/**
 * this function sets the socket member of the ClientFlow.
 * @param s = the new socket.
 */
void ClientFlow::setSocket(Socket* s) {
    this->socket = s;
}

/**
 * this function checks if a given string is a number.
 * @param s - the string
 * @return - return the answer
 */
bool ClientFlow::isNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}