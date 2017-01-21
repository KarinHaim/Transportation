#include "CalculateRoadThread.h"
#include "Search.h"

/**
 * this function is the constructor of the CalculateRoadThread object.
 * @param locker - a mutex to lock the frame of using the bfs algorithm.
 * @param paramRoad - a Road object to get the members needed.
 */
CalculateRoadThread::CalculateRoadThread(pthread_mutex_t *locker, Road* paramRoad) {
    this->calculateRoadLocker = locker;
    this->road = paramRoad;
}

/**
 * this function is the destructor of the CalculateRoadThread object.
 */
CalculateRoadThread::~CalculateRoadThread() {

}

/**
 * this function returns the start point of the road.
 * @return - the start point.
 */
Point* CalculateRoadThread::getStartP() {
    return this->road->getStartPCoordinates();
}

/**
 * this function returns the end point of the road.
 * @return - the end point.
 */
Point* CalculateRoadThread::getEndP(){
    return this->road->getEndPCoordinates();
}

/**
 * this function sets the Road object with the new road after calculation.
 * @param paramRoad - the new road.
 */
void CalculateRoadThread::setRoad(std::vector<Point*> paramRoad) {
    this->road->setRoad(paramRoad);
}

/**
 * this function is the static function operates the calculation, which the thread calls.
 * @param arg - a pointer to CalculateRoadThread object.
 * @return - NULL
 */
static void *calculateRoad(void* arg) {
    CalculateRoadThread* calculateRoadThread = (CalculateRoadThread*)arg;
    std::vector<Point*> road = Search<Point>::bfsTraversal(*calculateRoadThread->getStartP(), *calculateRoadThread->getEndP());
    calculateRoadThread->setRoad(road);
    return NULL;
}

/**
 * this function starts the bfs thread (create a new thread).
 */
void CalculateRoadThread::start() {
    //pthread_mutex_lock(this->calculateRoadLocker);
    pthread_create(&this->id, NULL, calculateRoad, this);
    //pthread_mutex_unlock(this->calculateRoadLocker);
}

/**
 * this function cancels the bfs thread.
 */
void CalculateRoadThread::stop() {
    pthread_cancel(this->id);
}

/**
 * this function wait for the bfs thread to end.
 */
void CalculateRoadThread::join() {
    pthread_join(this->id, NULL);
}
