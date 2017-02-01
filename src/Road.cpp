#include "../headers/Road.h"
#include "../headers/easylogging++.h"

/**
 * this is a constructor of Road.
 * @param map - a Map object
 * @param start - the starting point of the road
 * @param end - the ending point of the road.
 */
Road::Road(Map& map, Point start, Point end) {
    LOG(DEBUG) << "road's map is " << &map << "\n";
    this->start = map.getPointByCoordinates(start.getX(), start.getY());
    this->end = map.getPointByCoordinates(end.getX(), end.getY());
    this->currentLocation = NULL;
    this->isDoneCalculationOfRoad = false;
}

/**
 * this function is a default constructor.
 */
Road::Road() {
    this->start = Point();
    this->end = Point();
    this->currentLocation = NULL;
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
 * this function returns the road- vector of points
 * @return
 */
std::vector<Point> Road::getRoad() {
    return this->road;
}

/**
 * this function takes the road one step ahead.
 */
void Road::moveOneStep() {
    int i;
    //finding the index of the current location in the vector
    for(i = 0; i < this->road.size(); i++) {
        if (this->road[i] == this->currentLocation->getPosition())
            break;
    }

    //setting the current location point to be the next
    this->currentLocation->updateLocation(this->road[i+1]);
    LOG(DEBUG) << "location of road is " << this->currentLocation->getPosition();
}

/**
 * this function sets the road of Road
 * @param paramRoad - the road to set
 */
void Road::setRoad(std::vector<Point> paramRoad) {
    road = paramRoad;
}

/**
 * this function sets the currentLocation and changes it's value to the startingPoint.
 * @param location- the location to set.
 */
void Road::setLocation(Location* location) {
    this->currentLocation = location;
    this->currentLocation->updateLocation(this->start);
}

/*
 * this function returns the startingPoint of the road.
 * @return
 */
Point Road::getStart() {
    return this->start;
}

/*
 * this function returns the endingPoint of the road.
 * @return
 */
Point Road::getEnd() {
    return this->end;
}

/*
 * this function sets the bool member isDoneCalculationOfRoad to true.
 */
void Road::setCalculationOfRoadToDone() {
    this->isDoneCalculationOfRoad = true;
}

/*
 * this function returns the value of isDoneCalculationOfRoad.
 */
bool Road::isFinishedCalculationOfRoad() {
    return isDoneCalculationOfRoad;
}