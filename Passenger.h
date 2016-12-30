
#ifndef TRANSPORTATION_PASSENGER_H
#define TRANSPORTATION_PASSENGER_H

#include "Point.h"

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
//#include <boost/serialization>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
/**
 * this class defines a passenger.
 */
class Passenger {
    //serialization
    friend class boost::serialization::access;
//    friend ostream & operator<<(ostream &os, const Passenger &passenger);
//    friend ostream & operator<<(ostream &os, const Passenger *passenger);
//    friend istream & operator>>(istream &input, const Passenger &passenger);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & sourceP;
        ar & destinationP;
        ar & money;
    }
private:
    Point sourceP;
    Point destinationP;
    double money;
public:
    Passenger(Point source, Point destination);
    Passenger();
    ~Passenger();
    int getSatisfactionScore();
    void setMoney(double newMoney);
   // void pay(double finalTariff);
    double getMoney();
};


#endif //TRANSPORTATION_PASSENGER_H
