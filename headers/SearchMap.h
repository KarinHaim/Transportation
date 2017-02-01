
#ifndef TRANSPORTATION_SEARCHMAP_H
#define TRANSPORTATION_SEARCHMAP_H

#include "Vertex.h"
#include "Map.h"

class SearchMap {
private:
    int width;
    int height;
    std::vector< std::vector<Vertex*> > vertices;
    void initializeVertices(Map &map);
public:
    SearchMap(Map &map);
    ~SearchMap();
    Vertex* getVertexByPoint(Point point);
};


#endif //TRANSPORTATION_SEARCHMAP_H
