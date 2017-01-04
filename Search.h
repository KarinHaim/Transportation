
#ifndef TRANSPORTATION_SEARCH_H
#define TRANSPORTATION_SEARCH_H

#include "Searchable.h"
#include <queue>
#include <stack>
#include <vector>

/*
 * A class that includes search functions. Contains function for searching the
 * shortest path via bfs traversal.
 */
template<class T>
class Search {
public:
    //A constructor.
    Search();
    //A destructor.
    ~Search();
    //gets 2 teplates of start and end, and prints the points in the path between them in order of bfs traversal.
    static std::vector<T *> bfsTraversal(T &starting, T &ending) {
        std::queue<T *> nextToCheck;
        starting.setVisited();
        nextToCheck.push(&starting);

        std::vector<T *> adjacent;

        T* current = 0; //NULL
        while (!nextToCheck.empty()) {
            current = nextToCheck.front();
            nextToCheck.pop();
            //stop the traversal when reaching the searched point.
            if (*current == ending) {
                break;
            }

            adjacent = (*current).getAdjacentSearchables();
            for (unsigned int i=0; i<adjacent.size(); i++) {
                //pushing to the queue only points that weren't already visited
                if (!(*adjacent[i]).isVisited() && !(*adjacent[i]).isOccupied()) {
                    (*adjacent[i]).setFormer(current);
                    (*adjacent[i]).setVisited();
                    nextToCheck.push(adjacent[i]);
                }
            }
        }

        //find all the points in the path by passing over the former point recursively
        std::stack<T *> pointsInRoute;
        while (current != 0) { //NULL
            pointsInRoute.push(current);
            current = (*current).getFormer();
        }

        std::vector<T*> routeVerticesList;
        //popping the point that stored in the stack in reversed order and print each
        while (!pointsInRoute.empty()) {
            current = pointsInRoute.top();
            pointsInRoute.pop();
            //  std::cout << *current;
            routeVerticesList.push_back(current);
        }
        return routeVerticesList;
    }
};

#endif //TRANSPORTATION_SEARCH_H
