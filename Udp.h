
#ifndef TRANSPORTATION_UDP_H
#define TRANSPORTATION_UDP_H

#include "Socket.h"
#include <string>

class Udp: public Socket {
public:
    Udp(ProcessRole pr, u_short port, std::string ip = "127.0.0.1");
    void sendData(std::string data);
    int receiveData(char * buffer, int size);
};


#endif //TRANSPORTATION_UDP_H
