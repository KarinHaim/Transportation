#include "../headers/Point.h"

/**
 * this function is a constructor of Point.
 * @param paramX - x value
 * @param paramY - y value
 */
Point::Point(int paramX, int paramY) {
    x = paramX;
    y = paramY;
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
