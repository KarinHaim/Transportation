#include "threadBFS.h"

threadBFS::threadBFS(Road* paramRoad, &pthread_mutex_t locker) {
    this->road = paramRoad;
    this.bfsLocker = locker;
}

threadBFS::~threadBFS(){
    pthread_mutex_destroy(&this->bfsLocker);
}

void threadBFS::start() {
    pthread_mutex_lock(&this->bfsLocker);
    pthread_create(&this->id, NULL, calculateRoad, this);
    pthread_mutex_unlock(&this->bfsLocker);
}

void threadBFS::stop() {
    pthread_cancel(this->id);
}

void threadBFS::join() {
    pthread_join(this->id, NULL);
}

Point* threadBFS::getStartP() {
    return this->road->getStartPCoordinates();
}

Point* threadBFS::getEndP(){
    return this->road->getEndPCoordinates();
}

void threadBFS::setRoad(std::vector<Point*> paramRoad) {
    this->road->setRoad(paramRoad);
}

static void* calculateRoad(void* thisThread) {
    threadBFS* threadBfs = (threadBFS*)(thisThread);
    std::vector<Point*> road = Search<Point>::bfsTraversal(*threadBfs->getStartP(), *threadBfs->getEndP());
    threadBfs->setRoad(road);
    return NULL;
}