#include <stdlib.h>
#include "Tcp.h"

/**
 * this function is a constructor of the tcp class.
 * @param pr - which process is this.
 * @param port - the port to use
 * @param ip - the ip to use
 */
Tcp::Tcp(ProcessRole pr, u_short port, const char * ip): Socket(pr, port, ip) {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor < 0) {
        perror("error openning socket");
        exit(1);
    }
    if (pr == ProcessRole::CLIENT) {
        setConnect();
    }
    if (pr == ProcessRole::SERVER) {
        bindServer();
        setListenToConnections();
    }
}

/*Tcp::Tcp(int sd, ProcessRole pr, u_short port, const char * ip): Socket(sd, pr, port, ip) {
    if (pr == ProcessRole::CLIENT) {
        setConnect();
    }
    if (pr == ProcessRole::SERVER) {
        bindServer();
        //setListenToConnections();
    }
}*/

/**
 * this function is a destructor for the tcp class.
 */
Tcp::~Tcp() {

}

void Tcp::setListenToConnections() {
    if (listen(socketDescriptor, backlog) < 0) {
        perror("error listen");
        exit(1);
    }
}

void Tcp::setConnect() {
    if (connect(socketDescriptor, (struct sockaddr *) &other_addr, sizeof(other_addr)) < 0) {
        perror("error connect");
        exit(1);
    }
}

/**
 * this function sends the data via a socket.
 * @param data - the data to send.
 */
void Tcp::sendData(std::string data) {
    int sent_bytes = send(socketDescriptor, data.c_str(), data.size() + 1, 0);
    if (sent_bytes < 0)
        perror("error send");
}

/**
 * this function recieve data via a socket.
 * @param buffer - thw buffer of the data.
 * @param size - the size of it.
 * @return - bytes of the data.
 */
int Tcp::receiveData(char * buffer, int size) {
    //socklen_t slen = sizeof(struct sockaddr_in);
    int bytes = recv(socketDescriptor, buffer, size, 0);
    if (bytes < 0) {
        perror("error receive");
    }
    return bytes;
}

/**
 * this function acceptss client that connects to the socket and creates new socket for
 * communicating with it.
 * @return - new socket descriptor
 */
int Tcp::acceptClient() {
    socklen_t slen = sizeof(struct sockaddr_in);
    int newSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &other_addr, &slen);
    if (newSocketDescriptor < 0) {
        perror("error accept");
    }
    return newSocketDescriptor;
}