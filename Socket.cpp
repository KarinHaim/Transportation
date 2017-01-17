
#include <stdlib.h>
#include <unistd.h>
#include "Socket.h"

/**
 * this function is a constructor for socket.
 * @param processRole - the role of the process client/server
 */
Socket::Socket(ProcessRole pr, u_short port, const char * ip) {
    this->pr = pr;
    this->backlog = 0;
    initializeSocketEndPoints(port, ip);
}

Socket::Socket(int sd, ProcessRole pr, u_short port, const char * ip) {
    this->socketDescriptor = sd;
    this->pr = pr;
    this->backlog = 0;
    initializeSocketEndPoints(port, ip);
}

/**
 * this function is a destructor for socket.
 */
Socket::~Socket() {
    close(socketDescriptor);
}

/**
 * this function initialize the socket.
 * @param port - which port to open.
 * @param ip - the ip address to bind.
 */
void Socket::initializeSocketEndPoints(u_short port, const char * ip) {
    if (pr == ProcessRole::CLIENT) {
        memset(&other_addr, 0, sizeof(other_addr));
        other_addr.sin_family = AF_INET;
        other_addr.sin_port = htons(port);
        other_addr.sin_addr.s_addr = inet_addr(ip);
    }
    if (pr == ProcessRole::SERVER) {
        memset(&this_addr, 0, sizeof(this_addr));
        this_addr.sin_family = AF_INET;
        this_addr.sin_port = htons(port);
        this_addr.sin_addr.s_addr = INADDR_ANY;
    }
}

void Socket::bindServer() {
    if (bind(socketDescriptor, (struct sockaddr *) &this_addr, sizeof(this_addr)) < 0) {
        perror("error bind");
        exit(1);
    }
}