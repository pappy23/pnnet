/**
 * @file
 * Link object
 */

#ifndef LINK_H
#define LINK_H

#include "Includes.h"
#include "Object.h"
#include "Weight.h"

namespace pann
{
    class Net;

    //! Link between two neurons
    class Link : public Object
    {
    public:
        enum Direction { in, out };

    private:
        NeuronIter to;
        Direction direction;
        UINT latency;
        Weight* w; //!< Pointer to Weight object (might be shared between different links)

    private:
        Link()
        {
            // Default constructor required by boost::serialization
        };

    public:
        Link(const NeuronIter _to, const Direction _direction, Weight* _w, UINT _latency = 1) :
            to(_to),
            direction(_direction),
            w(_w),
            latency(_latency)
        {
            w->incUsageCount();
        };

        ~Link()
        {
            if( !w->decUsageCount() )
                delete w;
        };

        NeuronIter getTo()       { return to; };
        Direction getDirection() { return direction; };
        UINT getLatency()        { return latency; };
        Weight* getWeight()      { return w; };
    
    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"  Link\n";
            ost<<"   direction: "<<direction<<std::endl;
            //ost<<"   to: "<<to->first<<std::endl;
            w->printDebugInfo(ost);
        }

    private:
        friend class Net; //now Net is responsible fot 'to' serialization
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<Object>(*this);
            //ar & to; - it's impossible to serialize iterators :(
            ar & direction;
            ar & latency;
            ar & w;
        };

    };

}; //pann

#endif //LINK_H

