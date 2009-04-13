/*
 * class for saving/restoring networks
 */

#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <sstream>
#include <fstream>

#include "Includes/BoostSerialization.h"

#include "Exception.h"
#include "Net.h"
#include "Neuron.h"
#include "Link.h"
#include "Weight.h"

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
        void save(Net& _obj, std::string _filename) throw(E<Exception::FilesystemError>)
        {
            ofstream ofs(_filename.c_str());
            if(ofs.fail())
                throw E<Exception::FilesystemError>()<<"Storage::save(): failed to open file "<<_filename<<" for writing\n"; 

            cout<<"Saving net to "<<_filename<<"..."<<endl;
            SerializatorType oa(ofs);
            try {
                oa << BOOST_SERIALIZATION_NVP(_obj);
            } catch(boost::archive::archive_exception& e) {
                throw E<Exception::FilesystemError>()<<"Storage::save(): failed to save net. Boost exception thrown.\n";
            }

            ofs.close();
        }; //save

        template<class SerializatorType>
        void load(Net& _obj, std::string _filename) throw(E<Exception::FilesystemError>)
        {
            ifstream ifs(_filename.c_str());
            if(ifs.fail())
                throw E<Exception::FilesystemError>()<<"Storage::load(): failed to open file "<<_filename<<" for reading\n"; 
            
            cout<<"Loading net from "<<_filename<<"..."<<endl;
            SerializatorType ia(ifs);
            try {
                ia >> BOOST_SERIALIZATION_NVP(_obj);
            } catch(boost::archive::archive_exception& e) {
                throw E<Exception::FilesystemError>()<<"Storage::load(): failed to load net. Boost exception thrown.\n";
            }

            ifs.close();
        }; //load

        //Load net and automatically detect format
        void autoload(Net& _obj, std::string _filename) throw(E<Exception::FilesystemError>);
    }; //Storage

}; //pann

#endif //STORAGE_H

