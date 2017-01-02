
#ifndef TRANSPORTATION_CAB_H
#define TRANSPORTATION_CAB_H

#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include "CarManufacturer.h"
#include "Color.h"

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
using namespace std;

/**
 * this class defines an abstract class of Cab.
 */
class Cab {
    //serialization
    friend class boost::serialization::access;
 //   friend ostream & operator<<(ostream &os, const Cab &cab);
 //  friend ostream & operator<<(ostream &os, const Cab *cab);
 //   friend istream & operator>>(istream &input, const Cab &cab);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & speed;
        ar & manufacturer;
        ar & color;
        ar & tariff;
        ar & isOccupied;
    }

protected:
    int id;
    int speed;
    CarManufacturer manufacturer;
    Color color;
    double tariff;
    bool isOccupied;
public:
    Cab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff);
    Cab();
    virtual ~Cab();
    bool getIsOccupied();
    void setOccupation(bool occupation);
    double getTariff();
    int getID();
    int getSpeed();
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab)


#endif //TRANSPORTATION_CAB_H
