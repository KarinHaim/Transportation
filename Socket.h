
#ifndef TRANSPORTATION_SOCKET_H
#define TRANSPORTATION_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include "ProcessRole.h"

/**
 * this function defines the socket class.
 */
class Socket {
protected:
    int socketDescriptor;
    struct sockaddr_in this_addr;
    struct sockaddr_in other_addr;
    ProcessRole pr;
    int backlog;
public:
    Socket(ProcessRole pr, u_short port, const char * ip);
    Socket(int sd, ProcessRole pr, u_short port, const char * ip);
    virtual ~Socket();
    void initializeSocketEndPoints(u_short port, const char * ip = "127.0.0.1");
    void bindServer();
    virtual void sendData(std::string data) = 0;
    virtual int receiveData(char * buffer, int size) = 0;
    void setSocketDescriptor(int sd);
};

#endif //TRANSPORTATION_SOCKET_H