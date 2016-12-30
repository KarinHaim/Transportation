#ifndef TRANSPORTATION_CLOCK_H
#define TRANSPORTATION_CLOCK_H
#include <boost/archive/text_iarchive.hpp>
using namespace std;

class Clock {
    //serialization
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & currentTime;
    }
private:
    int currentTime;
public:
    Clock();
    ~Clock();
    int getCurrentTime();
    void updateTime();
};

#endif //TRANSPORTATION_CLOCK_H
