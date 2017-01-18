#include "CalculateRoadThread.h"
#include "Search.h"

CalculateRoadThread::CalculateRoadThread(pthread_mutex_t *locker, Road* paramRoad) {
    this->calculateRoadLocker = locker;
    this->road = paramRoad;
}

CalculateRoadThread::~CalculateRoadThread() {

}

Point* CalculateRoadThread::getStartP() {
    return this->road->getStartPCoordinates();
}

Point* CalculateRoadThread::getEndP(){
    return this->road->getEndPCoordinates();
}

void CalculateRoadThread::setRoad(std::vector<Point*> paramRoad) {
    this->road->setRoad(paramRoad);
}

static void *calculateRoad(void* arg) {
    CalculateRoadThread* calculateRoadThread = (CalculateRoadThread*)arg;
    std::vector<Point*> road = Search<Point>::bfsTraversal(*calculateRoadThread->getStartP(), *calculateRoadThread->getEndP());
    calculateRoadThread->setRoad(road);
    return NULL;
}

void CalculateRoadThread::start() {
    //pthread_mutex_lock(this->calculateRoadLocker);
    pthread_create(&this->id, NULL, calculateRoad, this);
    //pthread_mutex_unlock(this->calculateRoadLocker);
}

void CalculateRoadThread::stop() {
    pthread_cancel(this->id);
}

void CalculateRoadThread::join() {
    pthread_join(this->id, NULL);
}
