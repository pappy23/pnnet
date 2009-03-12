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

            boost::archive::text_oarchive oa(ofs);
            oa << obj;

            ofs.close();
        };

        static void load(Net& obj, std::string filename)
        {
            std::ifstream ifs(filename.c_str());
            if(ifs.fail())
                throw Exception::FilesystemError()<<"Storage::load(): failed to open file "<<filename<<" for reading\n"; 
            
            boost::archive::text_iarchive ia(ifs);
            ia >> obj;

            ifs.close();
        };
    };

}; //pann

#endif //STORAGE_H

