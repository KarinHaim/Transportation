
#ifndef TRANSPORTATION_CLIENTHANDLETHREAD_H
#define TRANSPORTATION_CLIENTHANDLETHREAD_H


#include <pthread.h>
#include "TaxiCenter.h"
#include "Socket.h"


/**
 * this class defines the thread functionality of handling the clients.
 */
class ClientHandleThread {
private:
    int id;
    pthread_t thread_id;
    pthread_mutex_t *clientHandleMessagesLock;
    pthread_mutex_t *taxiCenterLock;
    pthread_mutex_t *driversToClientHandlesMapLock;
    Socket* socket;
    TaxiCenter* taxiCenter;
    std::map<int, int>* driversIdToClientHandlesIdMap;
    std::vector<std::string>* clientHandlesMessages;
public:
    ClientHandleThread(int id, pthread_mutex_t *clientHandleMessagesLock,
                       pthread_mutex_t *taxiCenterLock,
                       pthread_mutex_t * drivesToClientHandlesMapLock, Socket* socket,
                       std::map<int, int>* driversIdToClientHandleIdMap,
                       std::vector<std::string>* clientHandlesMessages, TaxiCenter* taxiCenter);
    ~ClientHandleThread();
    void addDriver();
    void sendMessageToClient();
    void start();
    void join();
    void stop();
};


#endif //TRANSPORTATION_CLIENTHANDLETHREAD_H
