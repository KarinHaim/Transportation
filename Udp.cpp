
#include <stdlib.h>
#include "Udp.h"

Udp::Udp(ProcessRole pr, u_short port, const char * ip) {
    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0) {
        perror("error openning socket");
        //exit(1);
    }
    initializeSocket(pr, port, ip);
}

Udp::~Udp() {
    
}

void Udp::sendData(std::string data, int len) {
    int sent_bytes = sendto(socketDescriptor, data.c_str(), len + 1, 0, (struct sockaddr *) &other_addr, sizeof(this->other_addr));
    if (sent_bytes < 0)
        perror("error sendto");
}

int Udp::receiveData(char * buffer, int size) {
    socklen_t slen = sizeof(struct sockaddr_in);
    int bytes = recvfrom(socketDescriptor, buffer, size, 0, (struct sockaddr *) &other_addr, &slen);
    if (bytes < 0) {
        perror("error receivefrom");
    }
    return bytes;
}
