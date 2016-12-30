
#include <stdlib.h>
#include "Udp.h"

/**
 * this function is a constructor of the udp class.
 * @param pr - which process is this.
 * @param port - the port to use
 * @param ip - the ip to use
 */
Udp::Udp(ProcessRole pr, u_short port, const char * ip) {
    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0) {
        perror("error openning socket");
        //exit(1);
    }
    initializeSocket(pr, port, ip);
}

/**
 * this function is a destructor for the udp class.
 */
Udp::~Udp() {
    
}

/**
 * this function sends the data via a socket.
 * @param data - the data to send.
 */
void Udp::sendData(std::string data) {
    int sent_bytes = sendto(socketDescriptor, data.c_str(), data.size() + 1, 0, (struct sockaddr *) &other_addr, sizeof(this->other_addr));
    if (sent_bytes < 0)
        perror("error sendto");
}

/**
 * this function recieve data via a socket.
 * @param buffer - thw buffer of the data.
 * @param size - the size of it.
 * @return - bytes of the data.
 */
int Udp::receiveData(char * buffer, int size) {
    socklen_t slen = sizeof(struct sockaddr_in);
    int bytes = recvfrom(socketDescriptor, buffer, size, 0, (struct sockaddr *) &other_addr, &slen);
    if (bytes < 0) {
        perror("error receivefrom");
    }
    return bytes;
}