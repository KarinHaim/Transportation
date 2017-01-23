#include "CalculateRoadThread.h"
#include "Search.h"

/**
 * this function is the constructor of the CalculateRoadThread object.
 * @param locker - a mutex to lock the frame of using the bfs algorithm.
 * @param paramRoad - a Road object to get the members needed.
 */
CalculateRoadThread::CalculateRoadThread(pthread_mutex_t *locker, Road* paramRoad, Map* map) {
    this->calculateRoadLocker = locker;
    this->road = paramRoad;
    this->map = map;
}

/**
 * this function is the destructor of the CalculateRoadThread object.
 */
CalculateRoadThread::~CalculateRoadThread() {

}

/**
 * this function sets the Road object with the new road after calculation.
 * @param paramRoad - the new road.
 */
void CalculateRoadThread::setRoad(std::vector<Point*> paramRoad) {
    this->road->setRoad(paramRoad);
}

void CalculateRoadThread::calculateRoad() {
    pthread_mutex_lock(calculateRoadLocker);
    std::vector<Point*> road;
    try {
        road = Search<Point>::bfsTraversal(*this->road->getStart(), *this->road->getEnd());
    }
    catch (...) {
        this->map->clearSearch();
        pthread_mutex_unlock(calculateRoadLocker);
        return;
    }

    this->map->clearSearch();
    pthread_mutex_unlock(calculateRoadLocker);
    this->road->setRoad(road);
}

/**
 * this function is the static function operates the calculation, which the thread calls.
 * @param arg - a pointer to CalculateRoadThread object.
 * @return - NULL
 */
static void *callCalculateRoad(void* arg) {
    CalculateRoadThread* calculateRoadThread = (CalculateRoadThread*)arg;
    calculateRoadThread->calculateRoad();
    return NULL;
}

/**
 * this function starts the bfs thread (create a new thread).
 */
void CalculateRoadThread::start() {
    pthread_create(&this->id, NULL, callCalculateRoad, this);
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
