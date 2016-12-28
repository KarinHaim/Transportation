
#ifndef TRANSPORTATION_SEARCHABLE_H
#define TRANSPORTATION_SEARCHABLE_H

#include <vector>

/**
 * this class defines an interface of a searchable object.
 * @tparam T - the searchable object.
 */
template<class T>
class Searchable {
public:
    void setAdjacentSearchables(std::vector<T*> adjacent) {

    }
    std::vector<T*> getAdjacentSearchables() {

    }
    bool isVisited() {

    }
    void setVisited() {

    }
    void setFormer(T* formerSearchable) {

    }
    T* getFormer() {

    }
    bool isOccupied() {

    }
    void setOccupation(bool occupation) {

    }
    bool operator == (const T &other) {

    }
};



#endif //TRANSPORTATION_SEARCHABLE_H
