
#include <sys/socket.h>
#include "ClientHandleThread.h"
#include "Serialization.h"
//#include "boost/algorithm/string.hpp"
//#include <boost/log/trivial.hpp>

/**
 * this function is a constructor of the ClientHandleThread object.
 * @param id - the id of the driver.
 * @param lock - a mutex object to lock the needed resources.
 * @param socket - a socket object.
 * @param driversIdToClientHandleIdMap - a map object to match drivers and their thread.
 * @param clientHandlesMessages - a vector of messages of client handling.
 * @param taxiCenter  - a TaxiCenter object.
 */
ClientHandleThread::ClientHandleThread(int id, pthread_mutex_t *lock, Socket* socket,
 std::map<int, int>& driversIdToClientHandleIdMap, std::vector<std::string>& clientHandlesMessages,
 TaxiCenter& taxiCenter): id(id), lock(lock), socket(socket),
 driversIdToClientHandlesIdMap(driversIdToClientHandlesIdMap),
 clientHandlesMessages(clientHandlesMessages), taxiCenter(taxiCenter) {

}

/**
 * this function is a destructor of the ClientHandleThread class.
 */
ClientHandleThread::~ClientHandleThread() {

}

/**
 * this function receives a new driver and adds it to the taxi center.
 */
void ClientHandleThread::addDriver() {
    char buffer[40000];
    memset(buffer, '0', sizeof(buffer));
    socket->receiveData(buffer, sizeof(buffer));
    //std::cout << "thread " << id << "driver received";
    //BOOST_LOG_TRIVIAL(debug) << "thread " << id << "driver received";
    Driver *driver = deserialize<Driver>(buffer, sizeof(buffer));
    driversIdToClientHandlesIdMap[driver->getID()] = id;
    try {
        taxiCenter.addDriver(driver);
    }
    catch (...) {
        delete(driver);
        throw;
    }
    Cab* cab = taxiCenter.attachTaxiToDriver(driver, driver->getCabID());
    std::string serialized = serialize<Cab>(cab);
    socket->sendData(serialized);
}

/**
 * this function sends a message to the client, that fits it's mode.
 */
void ClientHandleThread::sendMessageToClient() {
    while(true) {
        pthread_mutex_lock(lock);
        std::string message = clientHandlesMessages[id];
        pthread_mutex_unlock(lock);
        if (message != "") {
            if (message.compare("exit") == 0)
                break;
            else {
                socket->sendData(clientHandlesMessages[id]);
                pthread_mutex_lock(lock);
                clientHandlesMessages[id] = "";
                pthread_mutex_unlock(lock);
            }
        }
    }
    delete(socket);
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