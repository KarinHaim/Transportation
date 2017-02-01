
#include "../headers/SearchMap.h"
#include "../headers/easylogging++.h"

/**
 * this is a constructor of SearchMap.
 * @param map - map of points.
 */
SearchMap::SearchMap(Map &map) {
    width = map.getWidth();
    height = map.getHeight();
    initializeVertices(map);
}

/**
 * this is a default constructor of SearchMap.
 */
SearchMap::~SearchMap() {
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            delete vertices[i][j];
        }
    }
}

/**
 * this function initializes the vertices on the SearchMap.
 */
void SearchMap::initializeVertices(Map &map) {
    for (int i = 0; i< width; i++) {
        vertices.push_back(std::vector<Vertex*>());
        for (int j = 0; j < height; j++) {
            try {
                vertices[i].push_back(new Vertex(map.getPointByCoordinates(i, j)));
            }
            catch (std::bad_alloc& exc){
                LOG(DEBUG) << "bad alloc\n";
            }
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j< height; j++) {
            std::vector<Vertex*> adjacent;
            //check if the Vertex is at the edge and has only 2 adjacent vertices.
            if (i != 0) {
                adjacent.push_back(vertices[i-1][j]);
            }
            if (j != height - 1) {
                adjacent.push_back(vertices[i][j+1]);
            }
            if (i != width - 1) {
                adjacent.push_back(vertices[i+1][j]);
            }
            if (j != 0) {
                adjacent.push_back(vertices[i][j-1]);
            }
            (*vertices[i][j]).setAdjacentSearchables(adjacent);
        }
    }
}

/**
 * this function gets a point in the map and returns the vertex of this point.
 * @param point
 * @return the matching vertex in the SearchMap
 */
Vertex* SearchMap::getVertexByPoint(Point point) {
    return vertices[point.getX()][point.getY()];
}