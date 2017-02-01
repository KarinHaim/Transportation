
#include "../headers/Vertex.h"

/**
 * this function is a constructor of Vertex.
 * @param positionPoint - point
 */
Vertex::Vertex(Point positionPoint): position(positionPoint) {
    visited = false;
    former = NULL;
}

/**
 * this is a destructor of Vertex.
 */
Vertex::~Vertex() {

}

/*
 * this function returns the position (point) of the Vertex
 * @return the point
 */
Point Vertex::getPosition() const {
    return position;
}

/**
 * this function sets the adjacent vertices of the Vertex.
 * @param adjacent  the adjacent vertices.
 */
void Vertex::setAdjacentSearchables(std::vector<Vertex*> adjacent) {
    adjacentVertices = adjacent;
}

/**
 * this function returns the adjacent vertices of the Vertex.
 * @return
 */
std::vector<Vertex*> Vertex::getAdjacentSearchables(){
    return adjacentVertices;
}

/**
 * this function returns if this Vertex was visited or not.
 * @return - a boolean answer.
 */
bool Vertex::isVisited() {
    return visited;
}

/**
 * this function sets the visited flag of Vertex.
 */
void Vertex::setVisited() {
    visited = true;
}

/**
 * this function sets the former Vertex of this Vertex.
 * @param formerSearchable
 */
void Vertex::setFormer(Vertex* formerSearchable) {
    former = formerSearchable;
}

/**
 * this function returns the former Vertex of this Vertex.
 * @return the former Vertex
 */
Vertex* Vertex::getFormer() {
    return former;
}

/**
 * this function returns if this Vertex's point is occupied or not.
 * @return a boolean answer.
 */
bool Vertex::isOccupied() {
    return position.isOccupied();
}

/**
 * this function sets the occupation flag of Vertex's point.
 * @param occupation- the new occupation.
 */
void Vertex::setOccupation(bool occupation) {
    position.setOccupation(occupation);
}

/**
 * the next functions operates operator overloading of Vertex.
 * @param other
 * @return- the result
 */
bool Vertex::operator == (const Vertex &other) const {
    return position == other.getPosition();
}

bool Vertex::operator != (const Vertex &other) const {
    return position != other.getPosition();
}