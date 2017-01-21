
#ifndef TRANSPORTATION_CALCULATEROADTHREAD_H
#define TRANSPORTATION_CALCULATEROADTHREAD_H


#include "Road.h"

/**
 * this class defines the thread functionality of calculating the road using the bfs algorithm.
 */
class CalculateRoadThread {
private:
    pthread_mutex_t *calculateRoadLocker;
    pthread_t id;
    Road* road;
public:
    CalculateRoadThread(pthread_mutex_t *locker, Road* paramRoad);
    ~CalculateRoadThread();
    void start();
    void stop();
    void join();
    Point* getStartP();
    Point* getEndP();
    void setRoad(std::vector<Point*> paramRoad);
};


#endif //TRANSPORTATION_CALCULATEROADTHREAD_H
