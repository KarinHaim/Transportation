
#include <gtest/gtest.h>
#include <stdlib.h>
#include "MainFlow.h"
#include "Udp.h"

/**
 * this is the main function which operates the program.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {
   /* testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/

    int port = atoi(argv[1]);
    Socket s = Udp(ProcessRole::SERVER, (u_short)port);


    MainFlow mainFlow;
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
    return 0;
}