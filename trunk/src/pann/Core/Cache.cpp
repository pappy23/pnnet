//Cache.cpp

#include "Cache.h"

namespace pann
{
    Cache::Cache()
    {
        coherent = false;
    } //Cache

    Cache::~Cache()
    {
    } //~Cache

    void
    Cache::touch()
    {
        coherent = false;
    } //touch
    
    void
    Cache::fixed()
    {
        coherent = true;
    } //fixed

    bool
    Cache::isOk() const
    {
        return coherent;
    } //isOk

}; //pann
