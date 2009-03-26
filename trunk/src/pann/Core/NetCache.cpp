//NetCache.cpp

#include "NetCache.h"

namespace pann
{
    void
    NetCache::flush() throw()
    {
        data.clear();
        touch();
    } //flush

}; //pann
