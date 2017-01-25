
#include <stdlib.h>
#include <unistd.h>
#include "Socket.h"

/**
 * this function is a constructor of the socket.
 * @param pr - the process role of the socket - client/server.
 * @param port - the port to the socket.
 * @param ip - the ip for the socket.
 */
Socket::Socket(ProcessRole pr, u_short port, const char * ip) {
    this->pr = pr;
    this->backlog = 0;
    initializeSocketEndPoints(port, ip);
}

/**
 * this function is a constructor of the socket.
 * @param sd - the socket descriptor of this socket.
 * @param pr - the process role of the socket - client/server.
 * @param port - the port to the socket.
 * @param ip - the ip for the socket.
 */
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
        if (strcmp(ip, "localhost"))
            other_addr.sin_addr.s_addr = inet_addr("localhost");
        else
            other_addr.sin_addr.s_addr = inet_addr(ip);
    }
    if (pr == ProcessRole::SERVER) {
        memset(&this_addr, 0, sizeof(this_addr));
        this_addr.sin_family = AF_INET;
        this_addr.sin_port = htons(port);
        this_addr.sin_addr.s_addr = INADDR_ANY;
    }
}

/**
 * this function binds the ip address given.
 */
void Socket::bindServer() {
    if (bind(socketDescriptor, (struct sockaddr *) &this_addr, sizeof(this_addr)) < 0) {
        perror("error bind");
        exit(1);
    }
}

/**
 * this function sets a new socket descriptor.
 * @param sd - the new socket descriptor.
 */
void Socket::setSocketDescriptor(int sd) {
    this->socketDescriptor = sd;
}