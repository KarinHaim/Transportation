#include <gtest/gtest.h>
#include <fstream>
#include "../MainFlow.h"
#include "../StandardCab.h"

/*
 * MainFlowTester is a test fixture class which includes tests of MainFlow class using
 * Google's Testing Framework.
 */
class MainFlowTester : public testing::Test {
protected:
    MainFlow* mainFlow;
    std::fstream in;
    std::streambuf *cinbuf;
    virtual void SetUp() {
        mainFlow = new MainFlow();
        in.open("input.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
       // cinbuf = std::cin.rdbuf();
      //  std::cin.rdbuf(in.rdbuf());
    }
    virtual void TearDown() {
        std::cin.rdbuf(cinbuf);
        in.close();
        delete(mainFlow);
    }
    //A method that handles closing opened file and redirecting cin's stream to file's.
    virtual void closeFileAndRedirectBuffers() {
        in.close();
        in.open("input.txt");
        cinbuf = std::cin.rdbuf();
        std::cin.rdbuf(in.rdbuf());
    }
public:
    //A default Constructor.
    MainFlowTester() {
    }
};

/*
 *The function tests that SetWorldRepresentation throws exception when width's input is a negative
 *number
 */
TEST_F(MainFlowTester, SetWorldRepresentationNegativeWidthTester) {
    in << "-7 4\n0\n"; //input -7 as width and 4 as height with 0 obstacles
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->setWorldRepresentation());
}

/*
 *The function tests that SetWorldRepresentation throws exception when height's input is a negative
 *number
 */
TEST_F(MainFlowTester, SetWorldRepresentationNegativeHeightTester) {
    in << "7 -4\n0\n"; //input 7 as width and -4 as height with 0 obstacles
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->setWorldRepresentation());
}

/*
 *The function tests that SetWorldRepresentation throws exception when width's input is zero
 */
TEST_F(MainFlowTester, SetWorldRepresentationZeroWidthTester) {
    in << "0 4\n0\n"; //input 0 as width and 4 as height with 0 obstacles
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->setWorldRepresentation());
}

/*
 *The function tests that SetWorldRepresentation throws exception when height's input is zero
 */
TEST_F(MainFlowTester, SetWorldRepresentationZeroHeightTester) {
    in << "4 0\n0\n"; //input 4 as width and 0 as height with 0 obstacles
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->setWorldRepresentation());
}

/*
 *The function tests that SetWorldRepresentation throws exception when obstacles points are not
 *in the range of the matrix of the world representation.
 */
TEST_F(MainFlowTester, setWorldRepresentationValidatePointsInMatrixTester) {
    in << "2 2\n2\n1,0\n3,2\n"; //input 2 as width and 2 as height with 2 obstacles, (1, 0) and (3,2)
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->setWorldRepresentation());
}

/*
 *The function tests that SetWorldRepresentation works for valid input and initializes the
 *map in taxi center
 */
TEST_F(MainFlowTester, SetWorldRepresentationValidInputTester) {
    in << "2 4\n0\n"; //input 2 as width and 4 as height with 0 obstacles
    closeFileAndRedirectBuffers();
    EXPECT_NO_THROW(mainFlow->setWorldRepresentation());
    Map* map = mainFlow->getTaxiCenter()->getMap();
    Map* expectedMap = new Map(2, 4);
    EXPECT_EQ(expectedMap->getWidth(), map->getWidth());
    EXPECT_EQ(expectedMap->getHeight(), map->getHeight());
    delete(expectedMap);
}

/*
 *The function tests that addTrip throws exception when starting and/or ending point is not
 *in the range of the matrix of the world representation.
 */
TEST_F(MainFlowTester, addTripValidateStartingAndEndingPointsInMatrixTester) {
    in << "2 1\n0\n"; //input 2 as width and 1 as height with 0 obstacles
    in << "2,0,0,3,3,1,3\n"; //input 2 as id, (0, 0) and (3,3) as starting and ending
    // points and 1 as passenger and 3 as tariff
    closeFileAndRedirectBuffers();
    mainFlow->setWorldRepresentation();
    EXPECT_ANY_THROW(mainFlow->addTrip());
}

/*
 *The function tests that addTrip not throws exception when the input's valid.
 */
TEST_F(MainFlowTester, addTripValidInputTester) {
    in << "4 4\n0\n"; //input 4 as width and 4 as height with 0 obstacles
    in << "2,0,0,3,3,1,3\n"; //input 2 as id, (0, 0) and (3,3) as starting and ending
    // points and 1 as passenger and 3 as tariff
    closeFileAndRedirectBuffers();
    mainFlow->setWorldRepresentation();
    EXPECT_NO_THROW(mainFlow->addTrip());
}

/*
 *The function tests that addTrip throws exception when passengersNum is a negative number.
 */
TEST_F(MainFlowTester, addTripPassengersNumNegativeTester) {
    in << "4 4\n0\n"; //input 4 as width and 4 as height with 0 obstacles
    in << "2,0,0,3,3,-3,3\n"; //input 2 as id, (0, 0) and (3,3) as starting and ending
    // points and -3 as passenger and 3 as tariff
    closeFileAndRedirectBuffers();
    mainFlow->setWorldRepresentation();
    EXPECT_ANY_THROW(mainFlow->addTrip());
}

/*
 *The function tests that addTrip throws exception when passengersNum is zero.
 */
TEST_F(MainFlowTester, addTripPassengersNumZeroTester) {
    in << "4 4\n0\n"; //input 4 as width and 4 as height with 0 obstacles
    in << "2,0,0,3,3,0,3\n"; //input 2 as id, (0, 0) and (3,3) as starting and ending
    // points and 0 as passenger and 3 as tariff
    closeFileAndRedirectBuffers();
    mainFlow->setWorldRepresentation();
    EXPECT_ANY_THROW(mainFlow->addTrip());
}

/*
 *The function tests that addTrip throws exception when passengersNum is over cab's
 *capacity of passengers.
 */
TEST_F(MainFlowTester, addTripPassengersNumMoreThanCabCapacityTester) {
    in << "4 4\n0\n"; //input 4 as width and 4 as height with 0 obstacles
    in << "2,0,0,3,3,7,3\n"; //input 2 as id, (0, 0) and (3,3) as starting and ending
    // points and 7 as passenger and 3 as tariff
    closeFileAndRedirectBuffers();
    mainFlow->setWorldRepresentation();
    EXPECT_ANY_THROW(mainFlow->addTrip());
}

/*
 *The function tests that AttachTaxiToDriver throws exception when driver id's input is a
 *negative number
 */
/*
TEST_F(MainFlowTester, AttachTaxiToDriverNegativeDriverIdTester) {
    TaxiCenter taxiCenter;
    Driver* driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2);
    taxiCenter.addDriver(driver);
    EXPECT_ANY_THROW(mainFlow.attachTaxiToDriver()); //input -45454 as driver's id
    delete driver;
}*/

/*
 *The function tests that AttachTaxiToDriver not throws exception when driver id's input is valid
 *number and that it creats in taxi center new taxi and driver
 */
/*
TEST_F(MainFlowTester, AttachTaxiToDriverValidInputTester) {
    TaxiCenter taxiCenter;
    EXPECT_NO_THROW(mainFlow.attachTaxiToDriver()); //input 789 as driver's id
    std::list<Driver*> drivers = taxiCenter.getDrivers();
    EXPECT_EQ(1, drivers.size());
    std::list<Cab*> cabs = taxiCenter.getCabs();
    EXPECT_EQ(1, cabs.size());
}*/

/*
 *The function tests that AddDriver not throws exception when taxi's id input is valid
 *number and that it creats in taxi center new taxi and driver
 */
TEST_F(MainFlowTester, AddDriverValidInputTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "45,25,D,2,45\n"; //input 45 as id, 25 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    closeFileAndRedirectBuffers();
    Map* map = new Map(20,20);
    mainFlow->setMap(map);
    mainFlow->addTaxi();
    EXPECT_NO_THROW(mainFlow->addDriver());

    std::vector<Driver*> drivers = mainFlow->getTaxiCenter()->getDrivers();
    EXPECT_EQ(1, drivers.size());
    std::vector<Cab*> cabs = mainFlow->getTaxiCenter()->getCabs();
    EXPECT_EQ(1, cabs.size());
    EXPECT_EQ(cabs[0]->getID(), 45);
}

/*
 *The function tests that AddDriver function throws exception when cabId's input is
 *a negative number
 */
TEST_F(MainFlowTester, AddDriverNegativeTaxiIdTester) {
    in << "45,52,D,2,-8\n"; //input 45 as id, 52 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId -8
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->addDriver());
}

/*
 *The function tests that AddDriver function throws exception when driver's age input is
 *a negative number
 */
TEST_F(MainFlowTester, AddDriverNegativeAgeTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "45,-5,D,2,45\n"; //input 45 as id, -5 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    closeFileAndRedirectBuffers();
    mainFlow->addTaxi();
    EXPECT_ANY_THROW(mainFlow->addDriver());
}

/*
 *The function tests that AddDriver function throws exception when driver's age input is
 *zero
 */
TEST_F(MainFlowTester, AddDriverZeroAgeTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "45,0,D,2,45\n"; //input 45 as id, 0 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    closeFileAndRedirectBuffers();
    mainFlow->addTaxi();
    EXPECT_ANY_THROW(mainFlow->addDriver());
}

/*
 *The function tests that AddDriver function throws exception when driver's age input is less
 *that 16
 */
TEST_F(MainFlowTester, AddDriverSmallAgeTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "45,9,D,2,45\n"; //input 45 as id, 9 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    closeFileAndRedirectBuffers();
    mainFlow->addTaxi();
    EXPECT_ANY_THROW(mainFlow->addDriver());
}

/*
 *The function tests that AddDriver function throws exception when driver's id input is
 *a negative number
 */
TEST_F(MainFlowTester, AddDriverNegativeIdTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "-45,25,D,2,45\n"; //input -45 as id, 25 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    closeFileAndRedirectBuffers();
    mainFlow->addTaxi();
    EXPECT_ANY_THROW(mainFlow->addDriver());
}

/*
 *The function tests that AddDriver function throws exception when driver's years of
 *experience input is a negative number
 */
TEST_F(MainFlowTester, AddDriverNegativeYearsOfExperienceTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "8,25,D,-9,45\n"; //input 8 as id, 25 as age, DIVRORCED as
    // meritalStatus and -9 as years of experience and cabId 45
    closeFileAndRedirectBuffers();
    mainFlow->addTaxi();
    EXPECT_ANY_THROW(mainFlow->addDriver());
}


/*
 *The function tests that AddDriver function not throws exception when the input is valid
 *and that it adds a driver in the taxi center.
 */
/*
TEST_F(MainFlowTester, AddDriverValidInputTester) {
    TaxiCenter taxiCenter;
    EXPECT_NO_THROW(mainFlow.addDriver()); //input 45 as id, 30 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience
    std::list<Driver*> drivers = taxiCenter.getDrivers();
    EXPECT_EQ(1, drivers.size());
}*/

/*
 *The function tests that AddTaxi function throws exception when cab's id input is
 *a negative number
 */
TEST_F(MainFlowTester, AddTaxiNegativeIdTester) {
    in << "-45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    closeFileAndRedirectBuffers();
    EXPECT_ANY_THROW(mainFlow->addTaxi());
}

/*
 *The function tests that AddTaxi function throws exception when cab's speed input is
 *a negative number
 */
/*
TEST_F(MainFlowTester, AddTaxiNegativeSpeedTester) {
    EXPECT_ANY_THROW(mainFlow.addTaxi()); //input 989 as id, -4 as speed, HONDA as
    // carManufacturer, RED as color and 9 as tariff
}*/

/*
 *The function tests that AddTaxi function throws exception when cab's tariff input is
 *a negative number
 */
/*
TEST_F(MainFlowTester, AddTaxiNegativeTariffTester) {
    EXPECT_ANY_THROW(mainFlow.addTaxi()); //input 989 as id, 4 as speed, HONDA as
    // carManufacturer, RED as color and -9 as tariff
} */

/*
 *The function tests that AddTaxi function not throws exception when input is valid and that it
 *adds taxi in the taxi center.
 */
TEST_F(MainFlowTester, AddTaxiValidInputTester) {
    in << "989,1,H,R\n"; //input 989 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    closeFileAndRedirectBuffers();
    EXPECT_NO_THROW(mainFlow->addTaxi());
    std::vector<Cab*> cabs = mainFlow->getTaxiCenter()->getCabs();
    EXPECT_EQ(1, cabs.size());
}

/*
 *The function tests that StartDriving not throws exception when called and that the driver gets
 *to it's trip end point.
 */
TEST_F(MainFlowTester, StartDrivingTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "8,25,D,2,45\n"; //input 8 as id, 25 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    in << "2,0,0,3,3,3,3\n"; //input 2 as id, (0, 0) and (3,3) as starting and ending
    // points and 3 as passenger and 3 as tariff
    closeFileAndRedirectBuffers();
    Map* map = new Map(4,4);
    this->mainFlow->setMap(map);
    mainFlow->getTaxiCenter()->setMap(map);
    mainFlow->addTaxi();
    mainFlow->addDriver();
    mainFlow->addTrip();
    EXPECT_NO_THROW(mainFlow->moveAllOneStep());
    EXPECT_EQ(*mainFlow->getTaxiCenter()->getDrivers()[0]->getLocation()->getPosition(), Point(3,3));
}

/*
 *The function tests that PrintDriversLocation returns driver's location and prints it
 */
TEST_F(MainFlowTester, PrintDriversLocationTester) {
    in << "45,1,H,R\n"; //input 45 as id, standard cab, HONDA as
    // carManufacturer, RED as color
    in << "8,25,D,2,45\n"; //input 8 as id, 25 as age, DIVRORCED as
    // meritalStatus and 2 as years of experience and cabId 45
    in << "8\n"; //input 8 as id of driver to print it's location
    closeFileAndRedirectBuffers();
    std::fstream out("output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    Map* map = new Map(4,4);
    this->mainFlow->setMap(map);
    mainFlow->getTaxiCenter()->setMap(map);
    mainFlow->addTaxi();
    mainFlow->addDriver();
    mainFlow->printDriversLocation();
    std::cout.rdbuf(coutbuf);
    out.close();
    out.open("output.txt");
    std::string output;
    std::getline(out, output);
    out.close();
    EXPECT_EQ(output, "(0,0)");
}