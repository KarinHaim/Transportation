
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
//    friend ostream & operator<<(ostream &os, const StandardCab &standardCab);
//    friend ostream & operator<<(ostream &os, const StandardCab *standardCab);
//    friend istream & operator>>(istream &input, const StandardCab &standardCab);
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
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
