
#ifndef TRANSPORTATION_UDP_H
#define TRANSPORTATION_UDP_H

#include "Socket.h"
#include <string>

class Udp: public Socket {
public:
    Udp(ProcessRole pr, u_short port, const char * ip = "127.0.0.1");
    ~Udp();
    void sendData(std::string data);
    int receiveData(char * buffer, int size);
};


#endif //TRANSPORTATION_UDP_H
