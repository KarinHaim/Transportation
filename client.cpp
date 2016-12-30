
#include <gtest/gtest.h>
#include <stdlib.h>
#include "ClientFlow.h"
#include "Udp.h"

#include "Serialization.h"

/**
 * this is the main function which operates the program of the client side.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {
   /* testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/

    const char * ip = argv[1];
    int port = atoi(argv[2]);
    Socket* socket = new Udp(ProcessRole::CLIENT, (u_short)port);
    /*s->sendData("hi", 2);
    char buffer[1024];
    s->receiveData(buffer, sizeof(buffer));
    std::cout << buffer << std::endl;*/
    /*Map* m = new Map(20,20);
    Driver *d = new Driver(123, 20, MeritalStatus::DIVORCED, 30, m);
    std::string s2 = serialize<Driver>(d);*/

    //Driver *d2 = deserialize<Driver>(s2);
    //std::cout << d2->getLocation()->getPosition();

    /*s->sendData(s2);
    char buffer[10240];
    s->receiveData(buffer, sizeof(buffer));*/

    ClientFlow mainFlow(socket);
    mainFlow.addDriver();
    mainFlow.flow();

    /*while(true) {
    }*/
    return 0;
}