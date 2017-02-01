
#ifndef TRANSPORTATION_VERTEX_H
#define TRANSPORTATION_VERTEX_H


#include "Point.h"

class Vertex {
private:
    Point position;
    bool visited;
    std::vector<Vertex*> adjacentVertices;
    Vertex* former;
public:
    //A constructor.
    Vertex(Point positionPoint);
    //A destructor.
    ~Vertex();
    //returns the position of the Vertex on a graph
    Point getPosition() const;
    void setAdjacentSearchables(std::vector<Vertex*> adjacent);
    std::vector<Vertex*> getAdjacentSearchables();
    bool isVisited();
    void setVisited();
    void setFormer(Vertex* formerSearchable);
    Vertex* getFormer();
    bool isOccupied();
    void setOccupation(bool occupation);
    bool operator == (const Vertex &other) const;
    bool operator != (const Vertex &other) const;
};


#endif //TRANSPORTATION_VERTEX_H
