
#ifndef TRANSPORTATION_SOCKET_H
#define TRANSPORTATION_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include "ProcessRole.h"

class Socket {
protected:
    int socketDescriptor;
    struct sockaddr_in this_addr;
    struct sockaddr_in other_addr;
public:
    void initializeSocket(ProcessRole pr, u_short port, std::string ip = "127.0.0.1");
    virtual void sendData(std::string data) = 0;
    virtual int recieveData(char * buffer, int size) = 0;
};


#endif //TRANSPORTATION_SOCKET_H