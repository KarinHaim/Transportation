
#ifndef TRANSPORTATION_CLIENTFLOW_H
#define TRANSPORTATION_CLIENTFLOW_H


#include "TaxiCenter.h"
#include "Cab.h"
#include "Driver.h"
#include "Point.h"
#include "CarManufacturer.h"
#include "Color.h"
#include "MeritalStatus.h"
#include "Socket.h"
#include <string>
#include <stdlib.h>
#include <sstream>

/**
 * this class controls the clientFlow of the taxi center.
 */
class ClientFlow {
private:
    Socket* socket;
    Driver* driver;
    void parseDriver(int &id, int &age, MeritalStatus &meritalStatus, int &yearsOfExp, int& cabID);
    MeritalStatus parseMeritalStatus(char status);
   // void parseId(int &id);
    //void validatePositiveNumber(int num);
    //void validatePositiveNoneZeroNumber(int num);
    void absorptionOfSeveralArgumentsInALine(std::vector<std::string> &arguments);
public:
    ClientFlow();
    ~ClientFlow();
    Driver* scanDriver();
    void flow();
    void setSocket(Socket* s);
    void addDriver(Driver* paramDriver);
    bool isNumber(const std::string &s);
};

#endif //TRANSPORTATION_CLIENTFLOW_H
