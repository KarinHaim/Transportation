#include <gtest/gtest.h>
#include "../TaxiCenter.h"
#include "../StandardCab.h"

/*
 * TaxiCenterTester is a test fixture class which includes tests of TaxiCenter class using
 * Google's Testing Framework.
 */
class TaxiCenterTester : public testing::Test {
protected:
    Map* map;
    TaxiCenter* taxiCenter;
    StandardCab* standardCab;
    Driver* driver;
    //Initializes the needed pointers each time a test is executed.
    virtual void SetUp() {
        taxiCenter = new TaxiCenter();
        taxiCenter->setMap(map);
    }
    virtual void TearDown() {
        delete(taxiCenter);
    }
public:
    //A constructor
    TaxiCenterTester() {
        map = new Map(20,20);
       // StandardCab* standardCab = NULL;
       // Driver* driver = NULL;
    }
    ~TaxiCenterTester() {
        delete(map);
    }
};

//The function tests that attachTaxiToDriver gets a real driver and attach him with a cab.
TEST_F(TaxiCenterTester, attachTaxiToDriverTester) {
    driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2, map);
    standardCab = new StandardCab();

    //'addTaxi' is tested separately in 'addTaxiTester'
    taxiCenter->addTaxi(standardCab);

    //'addDriver' is tested separately in 'addDriverTester'
    taxiCenter->addDriver(driver);

    /*
     * attachTaxiToDriver updates the driver's member of a *cab that it is available at the moment.
     * there is no option of a cab without a driver, besides the one we have just created, so
     * our driver and this cab suppose to be attached.
     */
    taxiCenter->attachTaxiToDriver(driver, standardCab->getID());

    //so these suppose to be equals now
    EXPECT_EQ(standardCab, driver->getCab());

    /**
     * now we check a case that the requested driver is not in the TaxiCenter.
     * we do that by create a new driver and try to attach him a cab without adding him to
     * the TaxiCenter.
     */
    Driver* nonExistingDriver = new Driver(55555, 30, MeritalStatus::DIVORCED, 2, map);
    //now we expect that when we try to attach the taxi to the driver, an exception will be thrown.
    EXPECT_ANY_THROW(taxiCenter->attachTaxiToDriver(nonExistingDriver, 111));
    delete(nonExistingDriver);
}

//rhis function tests that 'addDriver' really add the driver to taxi center.
TEST_F(TaxiCenterTester, addDriverTester) {
    driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2, map);
    standardCab = new StandardCab();
    taxiCenter->addTaxi(standardCab);
    //'addDriver' adds the driver to the end of the list of drivers in 'taxiCenter'
    taxiCenter->addDriver(driver);

    //so these suppose to be equals now
    EXPECT_EQ(driver, taxiCenter->getDrivers().back()); //'back' returns a reference to the last element in the list.

    /**
     * now we check if the driver that is added has an id that is not already exists.
     * we create a new driver with the same id and try to add it.
     */
    Driver* falseDriver = new Driver (12345, 3, MeritalStatus::SINGLE, 2, map);
    //now we expect that when we add the driver, an exception will be thrown.
    EXPECT_ANY_THROW(taxiCenter->addDriver(falseDriver));
    delete(falseDriver);
}


//this function tests that 'addCab' really add the cab to taxi center.
TEST_F(TaxiCenterTester, addTaxiTester) {
    //'addTaxi' adds the cab to the end of the list of cabs in 'taxiCenter'
    StandardCab* standardCab2 = new StandardCab(1234, 30, CarManufacturer::HONDA, Color::GREEN, 15);
    taxiCenter->addTaxi(standardCab2);

    //so these suppose to be equals now
    EXPECT_EQ(standardCab2, taxiCenter->getCabs().back()); //'back' returns a reference to the last element in the list.

    /**
     * now we check if the cab that is added has an id that is not already exists.
     * we create a new cab with the same id and try to add it.
     */
    StandardCab* falseCab = new StandardCab(1234, 50, CarManufacturer::FIAT, Color::RED, 15);
    //now we expect that when we add the cab, an exception will be thrown.
    EXPECT_ANY_THROW(taxiCenter->addTaxi(falseCab));
    delete (falseCab);
}

//this function tests that 'recieveMoneyFromDrivers' really recieve all the Money From all the drivers.
/*TEST_F(TaxiCenterTester, recieveMoneyFromDriversTester) {
    driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2);
    standardCab = new StandardCab();
    taxiCenter.addTaxi(standardCab);

    driver->getPaid(50);
    taxiCenter.addDriver(driver);
    /**
     *  'recieveMoneyFromDrivers' calls to driver.reportMoney() for all drivers (currently just one).
     *  the function 'reportMoney' is tested in 'DriverTester'
     */
/* taxiCenter.recieveMoneyFromDrivers();
 EXPECT_EQ(taxiCenter.getAllMoney(), 50);
 EXPECT_EQ(driver->getMoney(), 0);
}*/

//this function tests that 'addTrip' really add the trip to taxi center.
TEST_F(TaxiCenterTester, addTripTester) {
    //'addTrip' adds the trip to the end of the list of trips in 'taxiCenter'
    taxiCenter->addTrip(123, Point(0,0), Point(1,2), 3, 5, 0);

    //so these suppose to be equals now
    EXPECT_EQ(123, taxiCenter->getTrips()[0]->getID());
}
/**
 * this function is originally made to print the location but the instruction were to check the output and
 * not printing.
 */
TEST_F(TaxiCenterTester, getLocationOfDriverTester) {
    driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2, map);
    standardCab = new StandardCab(2, 2, CarManufacturer::FIAT, Color::PINK, 2);
    taxiCenter->addTaxi(standardCab);
//sets a new driver's location
    Point* point = new Point(1,1);
    //driver->setLocation(location);

//add this driver to taxiCenter
    taxiCenter->addDriver(driver);
    driver->updateLocation(point);
//  taxiCenter.getLocations().find(driver->getID())->first

//getting his location from taxiCenter
    Point location2 = taxiCenter->getLocationOfDriver(driver->getID());

//checking if it's the same.
    EXPECT_EQ(*point, location2);
    delete(point);
}

//this function tests that 'attachTripsToDriversTester' attaches the trips to the drivers correctly.

TEST_F(TaxiCenterTester, attachTripsToDriversTester) {
    driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2, map);
    //setting a trip and a driver at the same start point
    taxiCenter->addTrip(0, Point(0,0), Point(1,2), 3, 5, 0);
    // driver->setLocation(new Location(new Point(5,5)));
    taxiCenter->addDriver(driver);
    Point* point = new Point(0,0);
    driver->updateLocation(point);
    taxiCenter->attachTripsToDrivers();
    EXPECT_EQ(0, driver->getTrip()->getID());
    delete(point);
}


/**
 * the function "startAllDrivers" simply operates the function "startDriving" in "Driver" that is
 * tested there.
 */