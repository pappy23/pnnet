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

    protected:
        boost::shared_ptr<Weight> w; //!< Pointer to Weight object (may be shared between different links)

    public:
        const NeuronIter to;
        const Direction direction;
        const UINT latency;

        Link(NeuronIter _to, const Direction _direction, boost::shared_ptr<Weight> _w, UINT _latency = 1) :
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

        inline const boost::shared_ptr<Weight> getW() const
        {
            return w;
        };

        void printDebugInfo(std::ostringstream& ost)
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
            ar & w;
            ar & const_cast<NeuronIter&>(to);
            ar & const_cast<Direction&>(direction);
            ar & const_cast<UINT&>(latency);
        };

    };

}; //pann

#endif //LINK_H

