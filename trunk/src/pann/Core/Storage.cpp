//Storage.cpp

#include "Storage.h"

namespace pann
{
    namespace Storage
    {
        void autoload(Net& _obj, std::string _filename) throw(E<Exception::FilesystemError>)
        {
            try {
                load<xml_in>(_obj, _filename);
                return;
            } catch(...) {
            }

            try {
                load<txt_in>(_obj, _filename);
                return;
            } catch(...) {
            }

            try {
                load<bin_in>(_obj, _filename);
                return;
            } catch(...) {
            }

            throw E<Exception::FilesystemError>()<<"Storage::autoload(): Can't load "<<_filename<<"\n";
        } //load
    }; //Storage
}; //pann

