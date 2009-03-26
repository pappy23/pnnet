//Storage.cpp

#include "Storage.h"

using namespace std;
using namespace boost::archive;

namespace pann
{
    namespace Storage
    {
        void save(Net& _obj, string _filename)
        {
            ofstream ofs(_filename.c_str());
            if(ofs.fail())
                throw Exception::FilesystemError()<<"Storage::save(): failed to open file "<<_filename<<" for writing\n"; 

            cout<<"Saving net to "<<_filename<<"..."<<endl;
            xml_oarchive oa(ofs);
            oa << BOOST_SERIALIZATION_NVP(_obj);

            ofs.close();
        } //save

        void load(Net& _obj, string _filename)
        {
            ifstream ifs(_filename.c_str());
            if(ifs.fail())
                throw Exception::FilesystemError()<<"Storage::load(): failed to open file "<<_filename<<" for reading\n"; 
            
            cout<<"Loading net from "<<_filename<<"..."<<endl;
            xml_iarchive ia(ifs);
            ia >> BOOST_SERIALIZATION_NVP(_obj);

            ifs.close();
        } //load

    }; //Storage
}; //pann

