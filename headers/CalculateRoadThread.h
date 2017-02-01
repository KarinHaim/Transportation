
#ifndef TRANSPORTATION_CALCULATEROADTHREAD_H
#define TRANSPORTATION_CALCULATEROADTHREAD_H

#include "Trip.h"


/**
 * this class defines the thread functionality of calculating the road using the bfs algorithm.
 */
class CalculateRoadThread {
private:
    Trip* trip;
    Map map;
public:
    CalculateRoadThread(Trip* paramTrip, Map& map);
    ~CalculateRoadThread();
    void calculateRoad();
    static void *callCalculateRoad(void* arg);
};


#endif //TRANSPORTATION_CALCULATEROADTHREAD_H
