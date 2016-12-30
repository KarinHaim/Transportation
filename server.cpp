
#include <gtest/gtest.h>
#include "Udp.h"
#include "Serialization.h"
#include "ServerFlow.h"


/**
 * this is the main function which operates the program of the server side.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {
   /* testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/

    int port = atoi(argv[1]);
    Socket* socket = new Udp(ProcessRole::SERVER, (u_short)port);
    //char buffer[10240];
    /*s->receiveData(buffer, sizeof(buffer));
    std::cout << buffer << std::endl;
    s->sendData("sup", 3);*/
    /*s->receiveData(buffer, sizeof(buffer));
    Driver *d2 = deserialize<Driver>(buffer, sizeof(buffer));
    std::cout << d2->getLocation()->getPosition();*/

    ServerFlow mainFlow(socket);
    mainFlow.setWorldRepresentation();

    int operationNum;
    while(true) {
        std::cin >> operationNum;
        if (std::cin.fail())
            throw "not a number";
        if (operationNum < 1 || operationNum > 9)
            throw "invalid operation number";
        switch (operationNum) {
            case 1:
                mainFlow.addDrivers();
            case 2:
                mainFlow.addTrip();
                break;
            case 3:
                mainFlow.addTaxi();
                break;
            case 4:
                mainFlow.printDriversLocation();
                break;
            case 7:
                socket->sendData("exit");
                return 0;
            case 9:
                mainFlow.updateTime();
        }
    }
}