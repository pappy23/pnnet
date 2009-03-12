/**
 * @file
 * Weight object
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include "Includes.h"
#include "Object.h"

namespace pann
{

    /**
     * Weight object, used in pann::Link. Weight might be shared among different Links.
     * Link contain boost::shared_ptr<Weight> for this object
     */
    class Weight : public Object
    {
        UINT usageCount; ///< Used by weight update algorithms for shared weights

    public:
        Float value; ///< weight itself

        Weight(Float _value = 1) : 
            value(_value),
            usageCount(1) { };

        ~Weight() { };

        UINT incUsageCount()
        {
            return ++usageCount;
        };

        UINT decUsageCount()
        {
            if(--usageCount == 0)
                ; //FIXME
                //throw Exception::Unbelievable()<<"Weight::decUsageCount(): Kill me\n";

            return usageCount;
        };

        const UINT& getUsageCount()
        {
            return usageCount;
        };

        void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"   Weight\n";
            ost<<"    usageCount: "<<usageCount<<std::endl;
            ost<<"    value: "<<value<<std::endl;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<Object>(*this);
            ar & usageCount;
            ar & value;
        };

    };

}; //pann

#endif //WEIGHT_H

