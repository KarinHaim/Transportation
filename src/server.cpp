
//#include <gtest/gtest.h>
#include <stdlib.h>
#include <sstream>
#include "../headers/Udp.h"
#include "../headers/ServerFlow.h"
#include "../headers/Tcp.h"
#include "../headers/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

/**
 * this is the main function which operates the program of the server side.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);
    ServerFlow mainFlow = ServerFlow();

    Socket* socket = new Tcp(ProcessRole::SERVER, (u_short)port);
    mainFlow.setSocket(socket);

    mainFlow.setWorldRepresentation();

    mainFlow.acceptGuiClient();

    mainFlow.flow();

    return 0;
}

