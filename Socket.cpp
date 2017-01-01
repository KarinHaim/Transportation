
#include <stdlib.h>
#include <unistd.h>
//#include <cstdlib>
#include "Socket.h"

Socket::Socket() {
}

Socket::~Socket() {
    close(socketDescriptor);
}

void Socket::initializeSocket(ProcessRole pr, u_short port, const char * ip) {
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
        if (bind(socketDescriptor, (struct sockaddr *) &this_addr, sizeof(this_addr)) < 0) {
            perror("error bind");
            //exit(1);
        }
    }
}
