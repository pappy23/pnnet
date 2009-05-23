//NetCache.cpp

#include "NetCache.h"

namespace pann
{
    void
    NetCache::flush()
    {
        layers.clear();
        touch();
    } //flush

}; //pann
