/**
 * boost::serialization archive types, features and traits
 */

#ifndef PANN_INCLUDES_BOOSTSERIALIZATION_H_INCLUDED
#define PANN_INCLUDES_BOOSTSERIALIZATION_H_INCLUDED

//Archive types
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

//Common
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/base_object.hpp> 
//#include <boost/serialization/version.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/export.hpp>

//Traits
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#endif //PANN_INCLUDES_BOOSTSERIALIZATION_H_INCLUDED

