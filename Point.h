#ifndef TRANSPORTATION_POINT_H
#define TRANSPORTATION_POINT_H


#include <iostream>

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

/*
 * A class that represents a point on a graph, characterized by coordinate
 * x value and coordinate y value;
 */
class Point {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & x;
        ar & y;
        //ar & visited;
        //ar & adjacentPoints;
        //ar & former;
        //ar & occupied;
    }
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