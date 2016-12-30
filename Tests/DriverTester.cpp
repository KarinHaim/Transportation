#include <gtest/gtest.h>
#include "../Driver.h"
#include "../LuxuryCab.h"
#include "../StandardCab.h"
#include "../TaxiCenter.h"

/*
 * DriverTester is a test fixture class which includes tests of Driver class using
 * Google's Testing Framework.
 */
class DriverTester : public testing::Test {
protected:
    Map* map;
    Driver* driver;
    //Initializes the needed variables each time a test is executed.
    virtual void SetUp() {
        driver = new Driver(12345, 30, MeritalStatus::DIVORCED, 2, map);
    }
    virtual void TearDown() {
        delete(driver);
    }
public:
    //A constructor
    DriverTester() {
        map = new Map(20,20);
    }
    ~DriverTester() {
        delete(map);
    }
};

//This function tests that the function 'updateTrip' really updates the driver's trip member.
TEST_F(DriverTester, updateTripTester) {
    Trip* trip = new Trip(123, Point(0,0), Point(1,2), map, 3, 50, 0);
    driver->updateTrip(trip);
    EXPECT_EQ(trip, driver->getTrip());
}

//this function tests that the driver gets paid correctly.
/*TEST_F(DriverTester, getPaidTester) {
    driver.getPaid(50);
    //since the driver starts with 0 money so he suppose to have only 50 now
    EXPECT_EQ(driver.getMoney(), 50);
}*/

//this function tests that the function "resetMoney" reset the money of the driver to 0.
/*TEST_F(DriverTester, resetMoneyTester) {
    driver.getPaid(50);
    //"resetMoney" sets the driver's money to 0 so he suppose to have 0 now
    driver.resetMoney();
    EXPECT_EQ(driver.getMoney(), 0);
}*/

//this function tests that the function getMoneyFromPassengers collects correctly the money from the passengers.
/*TEST_F(DriverTester, getMoneyFromPassengersTester) {
    //creating a Trip with tariff 20 (say it was the input)
    Trip* trip = new Trip(000, Point(), Point(), Map(), 1, 20);

    //creating a Cab with tariff 2 (say it was the input)
    LuxuryCab* luxuryCab = new LuxuryCab (0, 0, CarManufacturer::FIAT, Color::BLUE, 2);

    driver.attachCab(luxuryCab);
    driver.updateTrip(trip);

    driver.getMoneyFromPassengers();
    //now we check that the function reduces money from passengers
    std::vector<Passenger*> passengers = trip->getPassengers(); //suppose to be only one passenger
    for (int i = 0; i <= passengers.size(); i++) {
        //suppose to be 0 money (as initialized)
        EXPECT_EQ(passengers[i]->getMoney(), 0);
    }
    //trip also deletes the passengers
    delete(trip);
    delete(luxuryCab);
}*/

//This function tests that the function 'attachCab' really attaches a driver with a requested cab.
TEST_F(DriverTester, attachCabTester) {
    //testing with luxury cab
    LuxuryCab* luxuryCab = new LuxuryCab();
    driver->attachCab(luxuryCab);
    EXPECT_EQ(luxuryCab, driver->getCab());

    //testing with standard cab
    StandardCab* standardCab = new StandardCab();
    driver->attachCab(standardCab);
    EXPECT_EQ(standardCab, driver->getCab());
    delete(luxuryCab);
    delete(standardCab);
}

/**
 * This function tests that the function 'calculateFinalTariff' calaulates the final tariff as
 * the multiplication of the cab's tariff and the trip's tariff.
 */
TEST_F(DriverTester, calculateFinalTariffTester) {
    //creating a Trip with tariff 20 (say it was the input)
    Trip* trip = new Trip(000, Point(0,0), Point(1,2), map, 3, 20, 0);

    //creating a Cab with tariff 2 (say it was the input)
    LuxuryCab* luxuryCab = new LuxuryCab (0, 0, CarManufacturer::FIAT, Color::BLUE, 2);

    //we checked the function 'attachCab' in 'attachCabTester'
    driver->attachCab(luxuryCab);
    //we chacked the function 'updateTrip' in 'updateTripTester'
    driver->updateTrip(trip);

    //it suppose to take the two and multiply
    driver->calculateFinalTariff();
    EXPECT_EQ(trip->getTariff()*luxuryCab->getTariff(), driver->getFinalTariff());
    delete(luxuryCab);
}

/**
 * the function "startDriving" simply operates the function "moveToEnd" in "Trip" which operate the function
 * "moveOneStep" that is tested in "Road".
 */