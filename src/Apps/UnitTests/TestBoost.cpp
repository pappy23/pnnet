
//Core dependencies
//#include <boost/foreach.hpp>
//#include <boost/thread.hpp>
//#include <boost/thread/barrier.hpp>
//#include <boost/functional/hash.hpp>
//#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>

//No need in Core
//#include <boost/random.hpp>
//#include <boost/tuple/tuple.hpp>
//#include <boost/function.hpp>
//#include <boost/lexical_cast.hpp>

//Only external Apps
//#include <boost/progress.hpp>
//#include <boost/assign/std.hpp>

//Misc.
//#include <boost/lambda/lambda.hpp>
//#include <boost/lambda/bind.hpp>
//#include <boost/any.hpp>

//Archive types
//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
//#include <boost/archive/polymorphic_text_oarchive.hpp>
//#include <boost/archive/polymorphic_text_iarchive.hpp>
//#include <boost/archive/polymorphic_binary_oarchive.hpp>
//#include <boost/archive/polymorphic_binary_iarchive.hpp>

//Common
//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/version.hpp>
//#include <boost/serialization/tracking.hpp>
//#include <boost/serialization/export.hpp>

//Traits
//#include <boost/serialization/map.hpp>
//#include <boost/serialization/list.hpp>
//#include <boost/serialization/vector.hpp>
//#include <boost/serialization/shared_ptr.hpp>

#include <boost/python.hpp>

//#include "Core/All.h"

#include <fstream>

const char* test()
{
    return "test\n";
}

BOOST_PYTHON_MODULE(test)
{
    using namespace boost::python;
    def("test", test);

    //python_export_Moo();
}
