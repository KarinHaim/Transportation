
#ifndef TRANSPORTATION_TCP_H
#define TRANSPORTATION_TCP_H


#include "Socket.h"
#include <string>

/**
 * this class defines the tcp protocol.
 */
class Tcp: public Socket {
public:
    Tcp(ProcessRole pr, u_short port, const char * ip = "127.0.0.1");
    //Tcp(int sd, ProcessRole pr, u_short port, const char * ip = "127.0.0.1");
    ~Tcp();
    void sendData(std::string data);
    int receiveData(char * buffer, int size);
    void setListenToConnections();
    void setConnect();
    int acceptClient();
};

#endif //TRANSPORTATION_TCP_H
