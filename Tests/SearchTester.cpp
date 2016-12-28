
#include <gtest/gtest.h>
#include "../Search.h"
#include "../Map.h"

/*
 * SearchTester is a test fixture class which includes tests of Search class using
 * Google's Testing Framework.
 */
class SearchTester : public testing::Test {
protected:
    Map* map;
    //Initializes the map each time a test is executed.
    virtual void SetUp() {
        map = new Map(4, 3);
    }
    virtual void TearDown() {
        delete(map);
    }
public:
    //A default constructor.
    SearchTester() {
    }
};

/*
 *The function tests BFSTraversal function with bottom left and right top edges points as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalBottomLeftAndRightTopPointsTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(0, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 1)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 2)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 2)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on the first row as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnFirstRowLeftToRightTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(0, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 0)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on middle row as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnMiddleRowLeftToRightTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(0, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 1));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on the last row as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnLastRowLeftToRightTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(0, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 2)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on first column as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnFirstColumnBottomUpTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(0, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on middle column as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnMiddleColumnBottomUpTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(2, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(2, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on last column as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnLastColumnBottomUpTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(3, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with bottom right and top left edges points as
 *parameters.
 */
TEST_F(SearchTester, BfsTraversalBottomRightAndTopLeftPointsTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on first row when first points x is
 *bigger than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnFirstRowRightToLeftTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 0)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on middle row when first points x is
 *bigger than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnMiddleRowRightToLeftTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 1));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 1)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on last row when first points x is
 *bigger than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnLastRowRightToLeftTester) {

    Point* startingPoint = map->getPointByCoordinates(Point(3, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 2)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on first column when first point y is
 *bigger than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnFirstColumnTopToBottomTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(0, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on middle column when first point y is
 *bigger than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnMiddleColumnTopToBottomTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(1, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(1, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on last column when first point y is
 *bigger than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnLastColumnTopToBottomTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(3, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}


/*
 *The function tests BFSTraversal function with points on first row when first point x is
 *smaller than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnFirstRowLeftToRightTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(1, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 0)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on middle row when first point x is
 *smaller than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnMiddleRowLeftToRightTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(1, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 1));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on last row when first point x is
 *smaller than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnLastRowLeftToRightTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(1, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on first column when first point y is
 *smaller than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnFirstColumnBottomUpTester) {
    delete(map);
    map = new Map(4, 4);
    Point* startingPoint = map->getPointByCoordinates(Point(0, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 3));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on middle column when first point y is
 *smaller than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnMiddleColumnBottomUpTester) {
    delete(map);
    map = new Map(4, 4);
    Point* startingPoint = map->getPointByCoordinates(Point(2, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(2, 3));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on last column when first point y is
 *smaller than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnLastColumnBottomUpTester) {
    delete(map);
    map = new Map(4, 4);
    Point* startingPoint = map->getPointByCoordinates(Point(3, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 3));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(3, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on first row when first points x is
 *bigger than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnFirstRowRightToLeftTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(2, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 0)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on middle row when first points x is
 *bigger than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnMiddleRowRightToLeftTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(2, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 1));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on last row when first points x is
 *bigger than seconds points x as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnLastRowRightToLeftTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(2, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 2)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on first column when first points y is
 *bigger than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnFirstColumnTopToBottomTester) {
    delete(map);
    map = new Map(4, 4);
    Point* startingPoint = map->getPointByCoordinates(Point(0, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(0, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(0, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on middle column when first points y is
 *bigger than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnMiddleColumnTopToBottomTester) {
    delete(map);
    map = new Map(4, 4);
    Point* startingPoint = map->getPointByCoordinates(Point(1, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(1, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on last column when first points y is
 *bigger than seconds points y as parameters.
 */
TEST_F(SearchTester, BfsTraversalPointsOnLastColumnTopToBottomTester) {
    delete(map);
    map = new Map(4, 4);
    Point* startingPoint = map->getPointByCoordinates(Point(3, 2));
    Point* endingPoint = map->getPointByCoordinates(Point(3, 0));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(3, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with points on different column and row
 */
TEST_F(SearchTester, BfsTraversalPointsOnDifferentColumnAndRowTester) {
    delete(map);
    map = new Map(6, 5);
    Point* startingPoint = map->getPointByCoordinates(Point(1, 1));
    Point* endingPoint = map->getPointByCoordinates(Point(4, 3));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 2)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 3)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 3)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(3, 3)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edge point and a point which is not edge
 *on different column and row
 */
TEST_F(SearchTester, BfsTraversalEdgePointAndPointOnDifferentColumnAndRowTester) {
    delete(map);
    map = new Map(6, 5);
    Point* startingPoint = map->getPointByCoordinates(Point(1, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(4, 3));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 2)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 3)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 3)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(3, 3)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests BFSTraversal function with edges points on different column and row
 */
TEST_F(SearchTester, BfsTraversalEdgePointsOnDifferentColumnAndRowTester) {
    delete(map);
    map = new Map(6, 3);
    Point* startingPoint = map->getPointByCoordinates(Point(3, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(1, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    std::vector<Point*> expectedPoints;
    expectedPoints.push_back(startingPoint);
    expectedPoints.push_back(map->getPointByCoordinates(Point(2, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 0)));
    expectedPoints.push_back(map->getPointByCoordinates(Point(1, 1)));
    expectedPoints.push_back(endingPoint);
    EXPECT_EQ(expectedPoints, traversalPoints);
}

/*
 *The function tests that BFSTraversal function isn't traversing through vertices
 * which are occupied
 */
TEST_F(SearchTester, BfsTraversalOccupiedVertexTraversalTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(1, 2));
    map->getPointByCoordinates(Point(2, 0))->setOccupation(true);

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    for (unsigned i = 0; i< traversalPoints.size(); i++) {
        EXPECT_FALSE((*traversalPoints[i]) == Point(2,0));
    }
}

/*
 *The function tests that BFSTraversal function doesn't change vertices occupation.
 */
TEST_F(SearchTester, BfsTraversalAllVerticesNotOccupiedTester) {
    Point* startingPoint = map->getPointByCoordinates(Point(3, 0));
    Point* endingPoint = map->getPointByCoordinates(Point(1, 2));

    std::vector<Point *> traversalPoints = Search<Point>::bfsTraversal(*startingPoint, *endingPoint);

    for (unsigned i = 0; i< traversalPoints.size(); i++) {
        EXPECT_FALSE((*traversalPoints[i]).isOccupied());
    }
}