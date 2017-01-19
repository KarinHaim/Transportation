#ifndef TRANSPORTATION_THREADBFS_H
#define TRANSPORTATION_THREADBFS_H

#include <pthread.h>
#include "Point.h"
#include "Search.h"
#include "Road.h"
//#include <sys/param.h>

class threadBFS {
private:
    pthread_mutex_t bfsLocker;
    pthread_t id;
    //Point* startP;
    //Point* endP;
    Road* road;
   // std::vector<Point*> calculated;



public:
    threadBFS(Road* paramroad);
    ~threadBFS();
    void start();
    void stop();
    void join();
    Point* getStartP();
    Point* getEndP();
    void setRoad(std::vector<Point*> paramRoad);


};
static void* calculateRoad(void* thisThread) ;


#endif //TRANSPORTATION_THREADBFS_H
