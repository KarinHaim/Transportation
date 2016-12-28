
#ifndef TRANSPORTATION_POINT_H
#define TRANSPORTATION_POINT_H

#include "Searchable.h"
#include <iostream>

/*
 * A class that represents a point on a graph, characterized by coordinate
 * x value and coordinate y value;
 */
class Point {
private:
    int x, y;
    bool visited;
    std::vector<Point*> adjacentPoints;
    Point* former;
    bool occupied;
public:
    //A constructor.
    Point(int paramX, int paramY);
    //A default constructor.
    Point();
    //A destructor.
    ~Point();
    //returns the x coordinate of the point
    int getX() const;
    //returns the y coordinate of the point
    int getY() const;


    void setAdjacentSearchables(std::vector<Point*> adjacent);
    std::vector<Point*> getAdjacentSearchables();
    bool isVisited();
    void setVisited();
    void clearVisited();
    void setFormer(Point* formerSearchable);
    Point* getFormer();
    bool isOccupied();
    void setOccupation(bool occupation);
    //defines Points behavior for '==' operator which is comparing if x and y coordinated equal
    bool operator == (const Point &other) const;
    bool operator != (const Point &other) const;
    friend std::ostream & operator << (std::ostream& os, const Point &obj);
};

#endif //TRANSPORTATION_POINT_H
