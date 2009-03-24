/*
 * class for saving/restoring networks
 */

#ifndef STORAGE_H
#define STORAGE_H

#include "Includes.h"
#include "Net.h"
#include "Exception.h"

namespace pann
{
    class Storage
    {
    public:
        static void save(Net& obj, std::string filename)
        {
            std::ofstream ofs(filename.c_str());
            if(ofs.fail())
                throw Exception::FilesystemError()<<"Storage::save(): failed to open file "<<filename<<" for writing\n"; 

            std::cout<<"Saving net to "<<filename<<"..."<<std::endl;
            boost::archive::xml_oarchive oa(ofs);
            oa << BOOST_SERIALIZATION_NVP(obj);

            ofs.close();
        };

        static void load(Net& obj, std::string filename)
        {
            std::ifstream ifs(filename.c_str());
            if(ifs.fail())
                throw Exception::FilesystemError()<<"Storage::load(): failed to open file "<<filename<<" for reading\n"; 
            
            std::cout<<"Loading net from "<<filename<<"..."<<std::endl;
            boost::archive::xml_iarchive ia(ifs);
            ia >> BOOST_SERIALIZATION_NVP(obj);

            ifs.close();
        };
    };

}; //pann

#endif //STORAGE_H

