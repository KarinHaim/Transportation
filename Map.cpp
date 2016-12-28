#include "Map.h"

/**
 * this is a constructor of map.
 * @param w - width of the map.
 * @param h - hight of the map.
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
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            delete points[i][j];
        }
    }
}

/**
 * this function initializes the points on the map.
 */
void Map::initializePoints() {
    for (int i=0; i<width; i++) {
        points.push_back(std::vector<Point*>());
        for (int j=0; j<height; j++) {
            points[i].push_back(new Point(i, j));
        }
    }

    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            std::vector<Point*> adjacent;
            //check if the Vertex is at the edge and has only 2 adjacent vertices.
            if (i != 0) {
                adjacent.push_back(points[i-1][j]);
            }
            if (j != height - 1) {
                adjacent.push_back(points[i][j+1]);
            }
            if (i != width - 1) {
                adjacent.push_back(points[i+1][j]);
            }
            if (j != 0) {
                adjacent.push_back(points[i][j-1]);
            }
            (*points[i][j]).setAdjacentSearchables(adjacent);
        }
    }
}

/**
 * this function gets a point and returns a pointer to it on the map.
 * @param point -the point we want
 * @return a pointer to it on the map
 */
Point* Map::getPointByCoordinates(Point point) {
    return points[point.getX()][point.getY()];
}

/**
 * this function updates the obstacles on the map.
 * @param obstacles - to be updated.
 */
void Map::updateObstacles(std::vector<Point> obstacles) {
    for (int i=0; i<obstacles.size(); i++) {
        getPointByCoordinates(obstacles[i])->setOccupation(true);
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
std:: vector < std::vector<Point*> > Map::getPoints() {
    return points;
}

//this function sets all points' former and visited field to initialized.
void Map::clearSearch() {
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            points[i][j]->clearVisited();
            points[i][j]->setFormer(NULL);
        }
    }
}