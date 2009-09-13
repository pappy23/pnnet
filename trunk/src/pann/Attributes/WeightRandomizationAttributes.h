#ifndef PANN_ATTRIBUTES_WEIGHTRANDOMIZATIONATTRIBUTES_H_INCLUDED
#define PANN_ATTRIBUTES_WEIGHTRANDOMIZATIONATTRIBUTES_H_INCLUDED

#include "Core/Attributes.h"

namespace pann {
    /**
     * Attributes used in neurons to draw network model
     * in pann_viewer
     */
    class WeightRandomizationAttributes : public Attributes
    {
    public:
        WeightRandomizationAttributes() : min(0), max(0) {};
        virtual ~WeightRandomizationAttributes() {};

        static const HashType getHash()
        {
            static HashType groupName = hash("WeightRandomizationAttributes");
            return groupName;
        };

    public:
        Float min;
        Float max;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<WeightRandomizationAttributes, Attributes>(
                    static_cast<WeightRandomizationAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(min)
                & BOOST_SERIALIZATION_NVP(max);
            };

    }; //RandomizeWeightsAttributes
    REGISTER_ATTRIBUTES_H(WeightRandomizationAttributes);

}; //pann

#endif //PANN_ATTRIBUTES_WEIGHTRANDOMIZATIONATTRIBUTES_H_INCLUDED

