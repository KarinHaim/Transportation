
#ifndef TRANSPORTATION_CALCULATEROADTHREAD_H
#define TRANSPORTATION_CALCULATEROADTHREAD_H


#include "Road.h"

class CalculateRoadThread {
private:
    pthread_mutex_t *calculateRoadLocker;
    pthread_t id;
    //Point* startP;
    //Point* endP;
    Road* road;
   // std::vector<Point*> calculated;
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
