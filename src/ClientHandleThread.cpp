
#include <sys/socket.h>
#include "../headers/ClientHandleThread.h"
#include "../headers/Serialization.h"
#include "../headers/easylogging++.h"

/**
 * this function is a constructor of the ClientHandleThread object.
 * @param id - the id of the driver.
 * @param lock - a mutex object to lock the needed resources.
 * @param socket - a socket object.
 * @param driversIdToClientHandleIdMap - a map object to match drivers and their thread.
 * @param clientHandlesMessages - a vector of messages of client handling.
 * @param taxiCenter  - a TaxiCenter object.
 */
ClientHandleThread::ClientHandleThread(int id, pthread_mutex_t *clientHandleMessagesLock,
 pthread_mutex_t *taxiCenterLock, pthread_mutex_t *driversToClientHandlesMapLock, 
 pthread_mutex_t *serializationLock, Socket* socket,
 std::map<int, int>* driversIdToClientHandleIdMap, std::vector<std::deque<std::string>>* clientHandlesMessages,
 TaxiCenter* taxiCenter) {
    this->id = id;
    LOG(DEBUG) << "clientHandleThread id is " << this->id << "\n";
    this->clientHandleMessagesLock = clientHandleMessagesLock;
    this->taxiCenterLock = taxiCenterLock;
    this->driversToClientHandlesMapLock = driversToClientHandlesMapLock;
    this->serializationLock = serializationLock;
    this->socket = socket;
    this->driversIdToClientHandlesIdMap = driversIdToClientHandleIdMap;
    this->clientHandlesMessages = clientHandlesMessages;
    this->taxiCenter = taxiCenter;
    sem_init(&notifyMessageSemaphore, 0, 0);
}

/**
 * this function is a destructor of the ClientHandleThread class.
 */
ClientHandleThread::~ClientHandleThread() {
	sem_destroy(&notifyMessageSemaphore);
    delete socket;
}

/**
 * this function receives a new driver and adds it to the taxi center.
 */
void ClientHandleThread::addDriver() {
	char buffer[40000] = { 0 };
    socket->receiveData(buffer, sizeof(buffer));
    pthread_mutex_lock(serializationLock);
    Driver *driver = deserialize<Driver>(buffer, sizeof(buffer));
    pthread_mutex_unlock(serializationLock);
    pthread_mutex_lock(driversToClientHandlesMapLock);
    (*driversIdToClientHandlesIdMap)[driver->getID()] = id;
    pthread_mutex_unlock(driversToClientHandlesMapLock);
    try {
        pthread_mutex_lock(taxiCenterLock);
        taxiCenter->addDriver(driver);
        pthread_mutex_unlock(taxiCenterLock);
    }
    catch (...) {
        delete(driver);
        throw;
    }
    pthread_mutex_lock(taxiCenterLock);
    Cab* cab = taxiCenter->attachTaxiToDriver(driver, driver->getCabID());
    pthread_mutex_unlock(taxiCenterLock);
    pthread_mutex_lock(serializationLock);
    std::string serialized = serialize<Cab>(cab);
    pthread_mutex_unlock(serializationLock);
    socket->sendData(serialized);
}

/**
 * this function sends a message to the client, that fits it's mode.
 */
void ClientHandleThread::sendMessageToClient() {
    while(true) {
        LOG(DEBUG) << "Waiting\n";
		sem_wait(&notifyMessageSemaphore);
        LOG(DEBUG) << "Woke up!\n";
        LOG(DEBUG) << "clientHandleThread id is " << id << "\n";
		while (true) {
			pthread_mutex_lock(clientHandleMessagesLock);
			if ((*clientHandlesMessages)[id].empty()) {
				pthread_mutex_unlock(clientHandleMessagesLock);
				break;
			}

			std::string message = (*clientHandlesMessages)[id].front();
			(*clientHandlesMessages)[id].pop_front();
			pthread_mutex_unlock(clientHandleMessagesLock);

			socket->sendData(message);

			if (message.compare("exit") == 0) {
				return;
			}
		}
    }
}

/**
 * this function is the static function the thread operates, which handle the client.
 * @param arg - a pointer to ClientHandleThread object.
 * @return - NULL.
 */
static void *handleClient(void *arg) {
    ClientHandleThread* clientHandleThread = (ClientHandleThread*)arg;
    clientHandleThread->addDriver();
    clientHandleThread->sendMessageToClient();
    return NULL;
}

/**
 * this function starts the client handle thread (create a new thread).
 */
void ClientHandleThread::start() {
    pthread_create(&thread_id, NULL, handleClient, this);
}

/**
 * this function wait for the client handle thread to end.
 */
void ClientHandleThread::join() {
    pthread_join(thread_id, NULL);
}


/**
 * this function cancels the client handle thread.
 */
void ClientHandleThread::stop() {
    pthread_cancel(thread_id);
}

void ClientHandleThread::notify()
{
    LOG(DEBUG) << "Notify\n";
	sem_post(&notifyMessageSemaphore);
}
