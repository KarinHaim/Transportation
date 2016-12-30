#include "Location.h"

/**
 * this function is a constructor for the Location.
 * @param position - the place of the location.
 */
Location::Location(Point* position) {
    this->position = position;
}

/**
 * this function is a default constructor of Location.
 */
Location::Location() {
    this->position = NULL;
}

/**
 * this function is a destructor for the Location.
 */
Location::~Location() {
}

/**
 * this function updated a new position for the location.
 * @param newPosition
 */
void Location::updateLocation(Point* newPosition) {
    this->position = newPosition;
}

/**
 * this function returns the position of the location.
 * @return the position point.
 */
Point* Location::getPosition() {
    return this->position;
}