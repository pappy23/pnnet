/*
 * class for saving/restoring networks
 */

#ifndef STORAGE_H
#define STORAGE_H

#include "Exception.h"

namespace pann
{
    class Net;

    namespace Storage
    {
        void save(Net& _obj, std::string _filename) throw(E<Exception::FilesystemError>);
        void load(Net& _obj, std::string _filename) throw(E<Exception::FilesystemError>);
    }; //Storage

}; //pann

#endif //STORAGE_H

