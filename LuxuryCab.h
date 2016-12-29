
#ifndef TRANSPORTATION_LUXURYCAB_H
#define TRANSPORTATION_LUXURYCAB_H

#include "Cab.h"

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
/**
 * this class defines a LuxuryCab which is a derived class of "Cab".
 */
class LuxuryCab : public Cab {
    //serialization
    friend class boost::serialization::access;
    friend ostream & operator<<(ostream &os, const LuxuryCab &luxuryCab);
    friend ostream & operator<<(ostream &os, const LuxuryCab *luxuryCab);
    friend istream & operator>>(istream &input, const LuxuryCab &luxuryCab);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & speed;
        ar & manufacturer;
        ar & color;
        ar & tariff;
        ar & isOccupied;
        ar & boost::serialization::base_object<Cab>(*this);
    }
public:
    LuxuryCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff);
    LuxuryCab();
    ~LuxuryCab();
    bool getIsOccupied();
    void setOccupation(bool occupation);
    double getTariff();
    int getID();
};

#endif //TRANSPORTATION_LUXURYCAB_H
