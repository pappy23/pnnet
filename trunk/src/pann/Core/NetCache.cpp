//NetCache.cpp

#include "NetCache.h"

namespace pann
{
    void
    NetCache::flush()
    {
        data.clear();
        touch();
    } //flush

}; //pann
