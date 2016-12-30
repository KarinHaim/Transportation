#ifndef TRANSPORTATION_SERIALIZATION_H
#define TRANSPORTATION_SERIALIZATION_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;
using namespace boost::iostreams;
/**
 * this function is a template method which deserialize an object.
 * @tparam T - the object type.
 * @param serial_str - ths string to deserialize.
 * @param size - the size of the string.
 * @return - the deserialized object.
 */

template<class T>
T *deserialize(char * serial_str, int size) {
    T *p;
    boost::iostreams::basic_array_source<char> device(serial_str, size);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s(device);
    boost::archive::binary_iarchive ia(s);
    ia >> p;
    return p;
}

/**
 * this function is a template method which serialize an object.
 * @tparam T - the object type.
 * @param object - the object to serialize.
 * @return - a serialized string.
 */
template<class T>
string serialize(T *object) {
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();
    return serial_str;
}

#endif //TRANSPORTATION_SERIALIZATION_H