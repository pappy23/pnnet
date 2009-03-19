/**
 * @file
 * Runtime cache object
 */

#ifndef CACHE_H
#define CACHE_H

#include "Includes.h"
#include "Type.h"
#include "Object.h"

namespace pann
{
    /**
     * Abstract cache object
     * In reality every class should inherit own SuperDuperCache from this class
     */
    class Cache : public Object
    {
        /* Public interface */
    public:
        Cache() : coherent(false) { };
        virtual ~Cache() { };

        virtual void flush() = 0;

        void touch()
        {
            coherent = false;
        };
        
        void fixed()
        {
            coherent = true;
        };

        bool isOk() const
        {
            return coherent;
        };

        /* Protected attributes */
    protected:
        bool coherent;

        /* Debug */
    public:
        virtual void printDebugInfo(std::ostringstream& ost) const = 0;
    };

    class NetCache : public Cache
    {
        /* Public types */
    public:
        typedef std::vector<NeuronIter> ThreadTaskType;
        typedef std::vector<ThreadTaskType> FrontType;

        /* Public members */
    public:
        std::vector<FrontType> data;

        /* Public interface */
    public:
        virtual void flush()
        {
            data.clear();
            touch();
        }

        /* Debug */
    public:
        virtual void printDebugInfo(std::ostringstream& ost) const
        {
            for(unsigned layers = 0; layers < data.size(); ++layers)
            {
                ost<<"Layer #"<<layers<<std::endl;
                for(unsigned threads = 0; threads < data[layers].size(); ++threads)
                {
                    ost<<"  Thread "<<threads<<": ";
                    for(unsigned n = 0; n < data[layers][threads].size(); ++n)
                        ost<<data[layers][threads][n]->first<<" ";
                    ost<<std::endl;
                }
                ost<<std::endl;
            }
        }
    };

}; //pann

#endif //CACHE_H

