#include <stdlib.h>
#include <errno.h>
#include "../headers/Tcp.h"

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

/**
 * this function listen to connections to tcp protocol.
 */
void Tcp::setListenToConnections() {
    if (listen(socketDescriptor, backlog) < 0) {
        perror("error listen");
        exit(1);
    }
}

/**
 * this function establish a new connection via tcp.
 */
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
	int sent_bytes = -1;
	do {
		sent_bytes = send(socketDescriptor, data.c_str(), data.size() + 1, MSG_NOSIGNAL);
	} while (-1 == sent_bytes && EINTR == errno);

    if (sent_bytes < 0)
        perror("error send");
}

/**
 * this function recieve data via a socket.
 * @param buffer - the buffer of the data.
 * @param size - the size of it.
 * @return - bytes of the data.
 */
int Tcp::receiveData(char * buffer, int size) {
    //socklen_t slen = sizeof(struct sockaddr_in);
	int bytes = -1;

	do {
		bytes = recv(socketDescriptor, buffer, size, 0);
	} while (-1 == bytes && EINTR == errno);

    if (bytes < 0) {
        perror("error receive");
    }
    return bytes;
}

/**
 * this function accepts client that connects to the socket and creates new socket for
 * communicating with it.
 * @return - new socket descriptor
 */
int Tcp::acceptClient() {
    socklen_t slen = sizeof(other_addr);
    //socklen_t slen = sizeof(struct sockaddr_in);
	
	int newSocketDescriptor = -1;
	do {
		newSocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &other_addr, &slen);
	} while (-1 == newSocketDescriptor && EINTR == errno);

    if (newSocketDescriptor < 0) {
        perror("error accept");
    }
    return newSocketDescriptor;
}