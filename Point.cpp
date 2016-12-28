#include "Point.h"

/**
 * this function is a constructor of Point.
 * @param paramX - x value
 * @param paramY - y value
 */
Point::Point(int paramX, int paramY) {
    x = paramX;
    y = paramY;
    visited = false;
    former = NULL;
    occupied = false;
}

/**
 * this function is a default constructor of Point.
 */
Point::Point() {
    x = 0;
    y = 0;
}

/**
 * this is a destructor of point.
 */
Point::~Point() {

}

/**
 * this function returns the x value of the point.
 * @return
 */
int Point::getX() const {
    return x;
}

/**
 * this function returns the y value of the point.
 * @return
 */
int Point::getY() const {
    return y;
}

/**
 * this function sets the adjacent points of the point.
 * @param adjacent  the adjacent points.
 */
void Point::setAdjacentSearchables(std::vector<Point*> adjacent) {
    adjacentPoints = adjacent;
}

/**
 * this function returns the adjacent points of the point.
 * @return
 */
std::vector<Point*> Point::getAdjacentSearchables(){
    return adjacentPoints;
}

/**
 * this function returns if this point has visited or not.
 * @return - a boolean answer.
 */
bool Point::isVisited() {
    return visited;
}

/**
 * this function sets the 'visites' flag of point.
 */
void Point::setVisited() {
    visited = true;
}

/**
 * this function sets the former point of this point.
 * @param formerSearchable
 */
void Point::setFormer(Point* formerSearchable) {
    former = formerSearchable;
}

/**
 * this function returns the former point of this point.
 * @return the former point
 */
Point* Point::getFormer() {
    return former;
}

/**
 * this function returns if this point is occupied or not.
 * @return a boolean answer.
 */
bool Point::isOccupied() {
    return occupied;
}

/**
 * this function sets the occupation flag of point.
 * @param occupation- the new occupation.
 */
void Point::setOccupation(bool occupation) {
    occupied = occupation;
}

/**
 * the next functions operates operator overloading of point.
 * @param other
 * @return- the result
 */
bool Point::operator == (const Point &other) const {
    return (x == other.getX()) && (y == other.getY());
}

bool Point::operator != (const Point &other) const {
    return (x != other.getX()) || (y != other.getY());
}

std::ostream& operator << (std::ostream& os, const Point &obj) {
    return os << "(" << obj.getX() << "," << obj.getY() << ")" << std::endl;
}

//this function sets visited field back to false.
void Point::clearVisited() {
    visited = false;
}