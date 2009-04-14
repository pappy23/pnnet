//Storage.cpp

#include "Storage.h"

namespace pann
{
    namespace Storage
    {
        void autoload(Net& _obj, std::string _filename)
        {
            try {
                std::cout<<"Trying XML...\n";
                load<xml_in>(_obj, _filename);
                return;
            } catch(...) {
            }

            try {
                std::cout<<"Trying TXT...\n";
                load<txt_in>(_obj, _filename);
                return;
            } catch(...) {
            }

            try {
                std::cout<<"Trying BIN...\n";
                load<bin_in>(_obj, _filename);
                return;
            } catch(...) {
            }

            throw E<Exception::FilesystemError>()<<"Storage::autoload(): Can't load "<<_filename<<"\n";
        } //load
    }; //Storage
}; //pann

