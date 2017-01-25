
#ifndef TRANSPORTATION_CLIENTHANDLETHREAD_H
#define TRANSPORTATION_CLIENTHANDLETHREAD_H


#include <pthread.h>
#include <semaphore.h>
#include <deque>
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
    pthread_mutex_t *serializationLock;
    Socket* socket;
    TaxiCenter* taxiCenter;
    std::map<int, int>* driversIdToClientHandlesIdMap;
    std::vector<std::deque<std::string>>* clientHandlesMessages;
    sem_t notifyMessageSemaphore;
public:
    ClientHandleThread(int id, pthread_mutex_t *clientHandleMessagesLock,
                       pthread_mutex_t *taxiCenterLock,
                       pthread_mutex_t * drivesToClientHandlesMapLock,
                       pthread_mutex_t *serializationLock, Socket* socket,
                       std::map<int, int>* driversIdToClientHandleIdMap,
                       std::vector<std::deque<std::string>>* clientHandlesMessages, TaxiCenter* taxiCenter);
    ~ClientHandleThread();
    void addDriver();
    void sendMessageToClient();
    void start();
    void join();
    void stop();
	void notify();
};


#endif //TRANSPORTATION_CLIENTHANDLETHREAD_H
