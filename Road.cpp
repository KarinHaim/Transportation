#include "Road.h"
#include "Search.h"
#include "easylogging++.h"

/**
 * this is a constructor of Road.
 * @param map - a Map object
 * @param start - the starting point of the road
 * @param end - the ending point of the road.
 */
Road::Road(Map* map, Point start, Point end) {
    LOG(DEBUG) << "road's map is " << map << "\n";
    this->start = map->getPointByCoordinates(start);
    this->end = map->getPointByCoordinates(end);
    this->currentLocation = NULL;
    this->existRoad = false;
}

/**
 * this function is a default constructor.
 */
Road::Road() {
    this->start = NULL;
    this->end = NULL;
    this->currentLocation = NULL;
    this->existRoad = false;
}

/**
 * this function is a destructor.
 */
Road::~Road() {
}

/**
 * this function returns the current location of the road.
 * @return
 */
Location* Road::getCurrentLocation() {
    return this->currentLocation;
}

/**
 * this fuction returns the road.
 * @return
 */
std::vector<Point*> Road::getRoad() {
    return this->road;
}

/**
 * this function takes the road one step ahead.
 */
void Road::moveOneStep() {
    int i;
    //finding the index of the current location in the vector
    for(i = 0; i < this->road.size(); i++) {
        if (*(this->road[i]) == *(this->currentLocation->getPosition()))
            break;
    }

    //setting the current location point to be the next
    this->currentLocation->updateLocation(this->road[i+1]);
    LOG(DEBUG) << "location of road is " << *this->currentLocation->getPosition();
}

/**
 * this function sets the road of Road
 * @param paramRoad - the road to set
 */
void Road::setRoad(std::vector<Point*> paramRoad) {
    road = paramRoad;
    this->existRoad = true;
}

void Road::setExistRoad(bool b) {
    this->existRoad = b;
}

bool Road::getExistRoad() {
    return this->existRoad;
}

/**
 * this function sets the currentLocation and changes it's value to the startingPoint.
 * @param location- the location to set.
 */
void Road::setLocation(Location* location) {
    this->currentLocation = location;
    this->currentLocation->updateLocation(this->start);
}

Point* Road::getStart() {
    return this->start;
}

Point* Road::getEnd() {
    return this->end;
}
