
#ifndef TRANSPORTATION_CAB_H
#define TRANSPORTATION_CAB_H

#include "CarManufacturer.h"
#include "Color.h"
#include <boost/serialization/export.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/utility.hpp>


/**
 * this class defines an abstract class of Cab.
 */
class Cab {
    //serialization
    friend class boost::serialization::access;
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


#endif //TRANSPORTATION_CAB_H

