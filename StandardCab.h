
#ifndef TRANSPORTATION_STANDARDCAB_H
#define TRANSPORTATION_STANDARDCAB_H

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
 * this class defines a Standard Cab which inherits from Cab.
 */
class StandardCab : public Cab {
    //serialization
    friend class boost::serialization::access;
    friend ostream & operator<<(ostream &os, const StandardCab &standardCab);
    friend ostream & operator<<(ostream &os, const StandardCab *standardCab);
    friend istream & operator>>(istream &input, const StandardCab &standardCab);
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
    StandardCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff);
    StandardCab();
    ~StandardCab();
    bool getIsOccupied();
    void setOccupation(bool occupation);
    double getTariff();
    int getID();
};

#endif //TRANSPORTATION_STANDARDCAB_H
