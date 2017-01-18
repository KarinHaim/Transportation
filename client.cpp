
//#include <gtest/gtest.h>
#include <stdlib.h>
#include "ClientFlow.h"
#include "Udp.h"
#include "Tcp.h"


/**
 * this is the main function which operates the program of the client side.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {

    const char * ip = argv[1];
    int port = atoi(argv[2]);
    Socket* socket = new Tcp(ProcessRole::CLIENT, (u_short)port, ip);

    ClientFlow mainFlow(socket);
    mainFlow.addDriver();
    mainFlow.flow();

    return 0;
}