
#ifndef TRANSPORTATION_DRIVER_H
#define TRANSPORTATION_DRIVER_H

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
//#include <boost/archive/binary_oarchive>
#include <boost/serialization>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "Trip.h"
#include "Cab.h"
#include "Location.h"
#include "MeritalStatus.h"
using namespace std;
using namespace boost::archive;
using namespace boost::serialization;
//using namespace boost::iostreams;

/**
 * this class defines a driver.
 */
class Driver {
    //serialization
    friend ostream & operator<<(ostream &os, const Driver &driver);
    friend ostream & operator<<(ostream &os, const Driver *driver);
    friend istream & operator>>(istream &input, const Driver &driver);
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & id;
        ar & age;
        ar & meritalStatus;
        ar & yearsOfExp;
        ar & avgSatisfaction;
        ar & map;
        ar & cab;
        ar & finalTariff;
        ar & trip;
        ar & location;
        ar & money;
        ar & totalNumOfPassengers;
    }
private:
    int id;
    int age;
    MeritalStatus meritalStatus;
    int yearsOfExp;
    int avgSatisfaction;
    Map* map;
    Cab *cab;
    double finalTariff;
    Trip *trip;
    Location *location;
    double money;
    int totalNumOfPassengers;
    void calculateAvgSatisfaction();
public:
    Driver(int id, int age, MeritalStatus meritalStatus, int yearsOfExp, Map* map);
    Driver();
    ~Driver();
    void updateTrip(Trip* trip);
    void attachCab(Cab * cab);
    //void addPassenger(Passenger* passenger);
    void updateLocation(Point* location);
    void calculateFinalTariff();
    //void getPaid(double cash);
    //void resetMoney(); //sets the money to 0
    //void getMoneyFromPassengers();
    void startDriving();

    //getters
    int getID();
    int getAge();
    MeritalStatus getMeritalStatus();
    int getYearsOfExp();
    int getAvgSatisfaction();
    //std::vector<Passenger*> getPassengers();
    Cab * getCab();
    double getFinalTariff();
    Trip* getTrip();
    Location* getLocation();
    double getMoney();

};

//BOOST_SERIALIZATION_ASSUME_ABSTRACT(Driver)
ostream & operator<<(ostream &os, const Driver &driver) {
    return os << driver.id << driver.age << driver.meritalStatus << driver.yearsOfExp << driver.avgSatisfaction <<
              driver.map << driver.cab << driver.finalTariff << driver.trip << driver.trip << driver.location <<
              driver.money << driver.totalNumOfPassengers;
}

/*ostream & operator<<(ostream &os, const Driver &driver) {
    std::string serial_str;

    boost::iostreams::back_insert_device<std::string> insertDevice(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(insertDevice);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    return oa;
}*/


  Driver deserialize(string serial_str) {
    Driver d;
      boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
      boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
      boost::archive::binary_iarchive ia(s2);
      ia >> d;

      return d;
  }



  string serialize(Driver *driver) {
      std::string serial_str;

      boost::iostreams::back_insert_device<std::string> insertDevice(serial_str);
      boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(insertDevice);
      boost::archive::binary_oarchive oa(s);
      oa << driver;
      s.flush();

      return serial_str;
  }


#endif //TRANSPORTATION_DRIVER_H