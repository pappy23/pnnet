//NetCache.cpp

#include "NetCache.h"

namespace pann
{
    void
    NetCache::flush() throw()
    {
        layers.clear();
        touch();
    } //flush

}; //pann
