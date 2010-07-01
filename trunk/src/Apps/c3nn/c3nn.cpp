
#include "pann-shit.h"
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

class NetConfigT
{
public:
    NetConfigT() : layers(5) {};
    virtual ~NetConfigT() {};

    int layers;

    /* Serialization */
private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_NVP(var);
        };
}; //NetConfigT

class ParentConfigT
{
public:
    ParentConfigT() {};
    virtual ~ParentConfigT() {};

public:
    vector<NetConfigT> nets;

    /* Serialization */
private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_NVP(children);
        };
}; //ParentConfigT

void save_config(const ParentConfigT & config, const string & filename)
{
    typedef boost::archive::xml_oarchive FormatT;

    ofstream ofs(filename.c_str());
    if(ofs.fail())
        throw IoError()<<"save_config: failed to open file "<<filename<<" for writing\n"; 

    FormatT oa(ofs);
    try {
        oa << BOOST_SERIALIZATION_NVP(config);
    } catch(boost::archive::archive_exception& e) {
        throw IoError()<<"save(): failed to save config. Boost exception thrown. What: "<<e.what()<<"\n";
    } catch(...) {
        throw IoError()<<"save(): unknown exception\n";
    }

    ofs.close();
}; //save_config

int main(int argc, char ** argv)
{
    ParentConfigT config;

    save_config(config, "c3nn-cfg.xml");

    return 0;
}; //main

