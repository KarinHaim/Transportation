
#include <gtest/gtest.h>
#include <stdlib.h>
#include "MainFlow.h"
#include "Udp.h"

#include "Serialization.h"

/**
 * this is the main function which operates the program.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {
   /* testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/

    const char * ip = argv[1];
    int port = atoi(argv[2]);
    Socket* s = new Udp(ProcessRole::CLIENT, (u_short)port);
    /*s->sendData("hi", 2);
    char buffer[1024];
    s->receiveData(buffer, sizeof(buffer));
    std::cout << buffer << std::endl;*/
    Map* m = new Map(20,20);
    Driver *d = new Driver(123, 20, MeritalStatus::DIVORCED, 30, m);
    std::string s2 = serialize<Driver>(d);
    s->sendData(s2, sizeof(s2));
    delete(s);

    /*MainFlow mainFlow;
    mainFlow.setWorldRepresentation();

    int operationNum;
    while(true) {
        std::cin >> operationNum;
        if (std::cin.fail())
            throw "not a number";
        if (operationNum < 1 || operationNum > 7)
            throw "invalid operation number";
        switch (operationNum) {
            case 1:
                mainFlow.addDriver();
                break;
            case 2:
                mainFlow.addTrip();
                break;
            case 3:
                mainFlow.addTaxi();
                break;
            case 4:
                mainFlow.printDriversLocation();
                break;
            case 6:
                mainFlow.startDriving();
                break;
            case 7:
                return 0;
        }
    }
    return 0;*/
}