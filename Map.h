
#ifndef TRANSPORTATION_MAP_H
#define TRANSPORTATION_MAP_H

#include "Point.h"
#include <vector>

using namespace std;

/**
 * this class defines the map (the grid).
 */
class Map {
    //serialization
    friend class boost::serialization::access;
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

#endif //TRANSPORTATION_MAP_H