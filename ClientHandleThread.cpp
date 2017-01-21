
#include <sys/socket.h>
#include "ClientHandleThread.h"
#include "Serialization.h"
//#include "boost/algorithm/string.hpp"
//#include <boost/log/trivial.hpp>

ClientHandleThread::ClientHandleThread(int id, pthread_mutex_t *lock, Socket* socket,
 std::map<int, int>& driversIdToClientHandleIdMap, std::vector<std::string>& clientHandlesMessages,
 TaxiCenter& taxiCenter): id(id), lock(lock), socket(socket),
 driversIdToClientHandlesIdMap(driversIdToClientHandlesIdMap),
 clientHandlesMessages(clientHandlesMessages), taxiCenter(taxiCenter) {

}

ClientHandleThread::~ClientHandleThread() {

}

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

static void *handleClient(void *arg) {
    ClientHandleThread* clientHandleThread = (ClientHandleThread*)arg;
    clientHandleThread->addDriver();
    clientHandleThread->sendMessageToClient();
    return NULL;
}

void ClientHandleThread::start() {
    pthread_create(&thread_id, NULL, handleClient, this);
}

void ClientHandleThread::join() {
    pthread_join(thread_id, NULL);
}

void ClientHandleThread::stop() {
    pthread_cancel(thread_id);
}