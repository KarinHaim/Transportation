#include "../headers/Map.h"
#include "../headers/easylogging++.h"

/**
 * this is a constructor of map.
 * @param w - width of the map.
 * @param h - height of the map.
 */
Map::Map(int w, int h) {
    width = w;
    height = h;
    initializePoints();
}

/**
 * this is a default constructor of map.
 */
Map::Map() {
    width = 0;
    height = 0;
}

/**
 * this is a destructor of map.
 */
Map::~Map() {
}

/**
 * this function initializes the points on the map.
 */
void Map::initializePoints() {
    for (int i=0; i<width; i++) {
        points.push_back(std::vector<Point>());
        for (int j=0; j<height; j++) {
            try {
                points[i].push_back(Point(i, j));
            }
            catch (std::bad_alloc& exc){
                LOG(DEBUG) << "bad alloc\n";
            }
        }
    }
}

/**
 * this function gets coordinates and returns point in the map with these coordinates.
 * @param x - the x coordinate
 * @param y - the y coordinate
 * @return the matching point in the map
 */
Point Map::getPointByCoordinates(int x, int y) {
    return points[x][y];
}

/**
 * this function updates the obstacles on the map.
 * @param obstacles - vector of points to be updated as obstacles.
 */
void Map::updateObstacles(std::vector<Point> obstacles) {
    for (int i=0; i<obstacles.size(); i++) {
        points[obstacles[i].getX()][obstacles[i].getY()].setOccupation(true);
    }
}

/**
 * this function returns the width of the map.
 * @return
 */
int Map::getWidth() {
    return width;
}

/**
 * this function returns the height of the map.
 * @return
 */
int Map::getHeight() {
    return height;
}

/**
 * this function returns the points on the map.
 * @return
 */
std:: vector < std::vector<Point> > Map::getPoints() {
    return points;
}


