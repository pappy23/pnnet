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
    };

}; //pann

#endif //LINK_H

