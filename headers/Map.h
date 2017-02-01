
#ifndef TRANSPORTATION_MAP_H
#define TRANSPORTATION_MAP_H

#include "Point.h"
#include <vector>


/**
 * this class defines the map (the grid).
 */
class Map {
private:
    int width;
    int height;
    std::vector< std::vector<Point> > points;
    void initializePoints();
public:
    Map(int w, int h);
    Map();
    ~Map();
    Point getPointByCoordinates(int x, int y);
    void updateObstacles(std::vector<Point> obstacles);
    int getWidth();
    int getHeight();
    std::vector < std::vector<Point> > getPoints();
};


#endif //TRANSPORTATION_MAP_H