/*
 * class for saving/restoring networks
 */
//TODO: Remove file IO from Core
#ifndef STORAGE_H
#define STORAGE_H

//#include "Includes/Std.h"
#include <fstream>
#include "Includes/BoostSerialization.h"

//#include "Exception.h"
//#include "Net.h"
//#include "Neuron.h"
//#include "Link.h"
//#include "Weight.h"

using namespace std;

namespace pann
{
    namespace Storage
    {
        typedef boost::archive::xml_oarchive    xml_out;
        typedef boost::archive::xml_iarchive    xml_in;
        typedef boost::archive::binary_oarchive bin_out;
        typedef boost::archive::binary_iarchive bin_in;
        typedef boost::archive::text_oarchive   txt_out;
        typedef boost::archive::text_iarchive   txt_in;

        template<class SerializatorType>
        void save(NetPtr obj, std::string filename)
        {
            if(!obj)
                throw Exception()<<"Storage::save(): Nothing to save!\n";

            ofstream ofs(filename.c_str());
            if(ofs.fail())
                throw IoError()<<"Storage::save(): failed to open file "<<filename<<" for writing\n"; 

            cout<<"Saving net to "<<filename<<"..."<<endl;
            SerializatorType oa(ofs);
            try {
              oa << BOOST_SERIALIZATION_NVP(obj);
            } catch(boost::archive::archive_exception& e) {
                throw IoError()<<"Storage::save(): failed to save net. Boost exception thrown. What: "<<e.what()<<"\n";
            } catch(...) {
                throw IoError()<<"Storage::save(): unknown exception\n";
            }

            ofs.close();
        }; //save

        template<class SerializatorType>
        void load(NetPtr& obj, std::string filename)
        {
            if(!obj)
                obj.reset(new Net());

            ifstream ifs(filename.c_str());
            if(ifs.fail())
                throw IoError()<<"Storage::load(): failed to open file "<<filename<<" for reading\n"; 

            cout<<"Loading net from "<<filename<<"..."<<endl;
            SerializatorType ia(ifs);
            try {
                ia >> BOOST_SERIALIZATION_NVP(obj);
            } catch(boost::archive::archive_exception& e) {
                throw IoError()<<"Storage::load(): failed to load net. Boost exception thrown. What: "<<e.what()<<"\n";
            } catch(...) {
                throw IoError()<<"Storage::load(): unknown exception\n";
            }

            ifs.close();
        }; //load
    }; //Storage
}; //pann

#endif //STORAGE_H

