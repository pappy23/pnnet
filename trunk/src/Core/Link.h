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
    //! Link between two neurons
    class Link : public Object
    {
    public:
        enum Direction { in, out };

    private:
        NeuronIter to;
        Direction direction;
        UINT latency;
        boost::shared_ptr<Weight> w; //!< Pointer to Weight object (may be shared between different links)

    private:
        Link()
        {
            // Default constructor required by boost::serialization
        };

    public:
        Link(const NeuronIter _to, const Direction _direction, const boost::shared_ptr<Weight> _w, UINT _latency = 1) :
            to(_to),
            direction(_direction),
            w(_w),
            latency(_latency)
        {
            w->incUsageCount();
        };

        ~Link()
        {
            w->decUsageCount();
        };

        NeuronIter getTo()                      { return to; };
        Direction getDirection()                { return direction; };
        UINT getLatency()                       { return latency; };
        boost::shared_ptr<Weight> getWeight()   { return w; };
    
    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"  Link\n";
            ost<<"   direction: "<<direction<<std::endl;
            //ost<<"   to: "<<to->first<<std::endl;
            w->printDebugInfo(ost);
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<Object>(*this);
            ar & to;
            ar & direction;
            ar & latency;
            ar & w;
        };

    };

}; //pann

#endif //LINK_H

