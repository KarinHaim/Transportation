
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
    Map* map;
public:
    CalculateRoadThread(pthread_mutex_t *locker, Road* paramRoad, Map* map);
    ~CalculateRoadThread();
    void start();
    void stop();
    void join();
    Point* getStartP();
    Point* getEndP();
    Map* getMap();
    void calculateRoad();
    void setRoad(std::vector<Point*> paramRoad);
};


#endif //TRANSPORTATION_CALCULATEROADTHREAD_H
