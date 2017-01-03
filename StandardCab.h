
#ifndef TRANSPORTATION_STANDARDCAB_H
#define TRANSPORTATION_STANDARDCAB_H

#include "Cab.h"

using namespace std;

/**
 * this class defines a Standard Cab which inherits from Cab.
 */
class StandardCab : public Cab {
    //serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & boost::serialization::base_object<Cab>(*this);
    }
public:
    StandardCab(int id, int speed, CarManufacturer manufacturer, Color color, double tariff);
    StandardCab();
    ~StandardCab();
};

BOOST_CLASS_EXPORT(StandardCab)

#endif //TRANSPORTATION_STANDARDCAB_H
