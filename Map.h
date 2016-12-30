
#ifndef TRANSPORTATION_MAP_H
#define TRANSPORTATION_MAP_H

#include "Point.h"
#include <vector>
#include "Point.h"

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/**
 * this class defines the map(the grid).
 */
class Map {
    //serialization
    friend class boost::serialization::access;
//    friend ostream & operator<<(ostream &os, const Map &map);
//    friend ostream & operator<<(ostream &os, const Map *map);
//    friend istream & operator>>(istream &input, const Map &map);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & width;
        ar & height;
        ar & points;
    }
private:
    std::vector< std::vector<Point*> > points;
    int width;
    int height;
    void initializePoints();
public:
    Map(int w, int h);
    Map();
    ~Map();
    Point* getPointByCoordinates(Point point);
    void updateObstacles(std::vector<Point> obstacles);
    int getWidth();
    int getHeight();
    std:: vector < std::vector<Point*> > getPoints();
    void clearSearch();
};
/*
ostream & operator<<(ostream &os, const Map &map) {
   // os << map.width << map.height << map.points;
   // os << map.width << map.height;
}*/
#endif //TRANSPORTATION_MAP_H
