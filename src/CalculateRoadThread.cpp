#include "../headers/CalculateRoadThread.h"
#include "../headers/Search.h"
#include "../headers/SearchMap.h"

/**
 * this function is the constructor of the CalculateRoadThread.
 * @param paramTrip - trip which it's road will be calculated
 * @param map - map of points which the trip is defined on
 */
CalculateRoadThread::CalculateRoadThread(Trip* paramTrip, Map& map) {
    this->trip = paramTrip;
    this->map = map;
}

/**
 * this function is the destructor of the CalculateRoadThread.
 */
CalculateRoadThread::~CalculateRoadThread() {

}

/*
 * this function creates map for the search, runs the search algorithm and updates the resulting
 * road in the trip.
 */
void CalculateRoadThread::calculateRoad() {
    SearchMap searchMap(map);
    std::vector<Vertex*> road = Search<Vertex>::bfsTraversal(*searchMap.getVertexByPoint(this->trip->getRoad()->getStart()), *searchMap.getVertexByPoint(this->trip->getRoad()->getEnd()));
    this->trip->getRoad()->setCalculationOfRoadToDone();

    vector<Point> pointRoad;
    for (int i=0; i<road.size(); i++) {
        pointRoad.push_back(road[i]->getPosition());
    }
    this->trip->getRoad()->setRoad(pointRoad);
    this->trip->getRoad()->setCalculationOfRoadToDone();
}

/**
 * this function is the static function that calls the calculation method.
 * @param arg - a pointer to CalculateRoadThread object.
 * @return - NULL
 */
void * CalculateRoadThread::callCalculateRoad(void* arg) {
    CalculateRoadThread* calculateRoadThread = (CalculateRoadThread*)arg;
    calculateRoadThread->calculateRoad();
    return NULL;
}

