//Storage.cpp

#include <iostream>
#include <sstream>
#include <fstream>

#include "Includes/BoostSerialization.h"

#include "Storage.h"

#include "Net.h"
#include "Neuron.h"
#include "Link.h"
#include "Weight.h"

using namespace std;
using namespace boost::archive;

namespace pann
{
    namespace Storage
    {
        //TODO Make switch between binary/xml format, because sml takes too much space
        void save(Net& _obj, string _filename) throw(E<Exception::FilesystemError>)
        {
            ofstream ofs(_filename.c_str());
            if(ofs.fail())
                throw E<Exception::FilesystemError>()<<"Storage::save(): failed to open file "<<_filename<<" for writing\n"; 

            cout<<"Saving net to "<<_filename<<"..."<<endl;
            binary_oarchive oa(ofs);
            try {
                oa << BOOST_SERIALIZATION_NVP(_obj);
            } catch(boost::archive::archive_exception& e) {
                throw E<Exception::FilesystemError>()<<"Storage::save(): failed to save net. Boost exception thrown.\n";
            }

            ofs.close();
        } //save

        void load(Net& _obj, string _filename) throw(E<Exception::FilesystemError>)
        {
            ifstream ifs(_filename.c_str());
            if(ifs.fail())
                throw E<Exception::FilesystemError>()<<"Storage::load(): failed to open file "<<_filename<<" for reading\n"; 
            
            cout<<"Loading net from "<<_filename<<"..."<<endl;
            binary_iarchive ia(ifs);
            try {
                ia >> BOOST_SERIALIZATION_NVP(_obj);
            } catch(boost::archive::archive_exception& e) {
                throw E<Exception::FilesystemError>()<<"Storage::load(): failed to load net. Boost exception thrown.\n";
            }

            ifs.close();
        } //load

    }; //Storage
}; //pann

