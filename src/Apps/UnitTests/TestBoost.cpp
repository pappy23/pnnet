
//Core dependencies
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/functional/hash.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

//No need in Core
#include <boost/random.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

//Only external Apps
#include <boost/progress.hpp>
#include <boost/assign/std.hpp>

//Misc.
//#include <boost/lambda/lambda.hpp>
//#include <boost/lambda/bind.hpp>
//#include <boost/any.hpp>

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
#include <boost/serialization/version.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/export.hpp>

//Traits
#include <boost/serialization/map.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <fstream>

class AF {};
class AF1 : public AF {};
class AF2 : public AF {};

class BasicN
{
public:
    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive & ar, const unsigned int version)
    {
        std::cout<<"BasicN\n";
    }
};

template<class T> class N : public BasicN
{
public:
    typedef T AF_T;
    int a;

    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BasicN) & BOOST_SERIALIZATION_NVP(a);
        std::cout<<"N\n";
    }

};

int main()
{
    using namespace std;

    BasicN* n1 = new N<AF1>();
    BasicN* n2 = new N<AF2>();

    ofstream ofs("test.txt");
    boost::archive::xml_oarchive oa(ofs);
    oa<<BOOST_SERIALIZATION_NVP(n1)<<BOOST_SERIALIZATION_NVP(n2);

    return 0;
}
