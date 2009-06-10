#ifndef LMSATTRIBUTES_H
#define LMSATTRIBUTES_H

#include "Core/Attributes.h"

namespace pann
{
    class LmsNetAttributes : public Attributes
    {
    public:
        LmsNetAttributes() : learningRate(0.3), learningMomentum(0.5), epoch(1), annealingTSC(10) {};
        virtual ~LmsNetAttributes() {};

        static const HashType getHash()
        {
            static HashType groupName = hash("LmsNetAttributes");
            return groupName;
        };

    public:
        Float learningRate;
        Float learningMomentum;
        Float epoch;
        Float annealingTSC;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<LmsNetAttributes, Attributes>(
                    static_cast<LmsNetAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(learningRate)
                & BOOST_SERIALIZATION_NVP(learningMomentum)
                & BOOST_SERIALIZATION_NVP(epoch)
                & BOOST_SERIALIZATION_NVP(annealingTSC);
            };

    }; //LmsNetAttributes
    ADD_PTR_TYPEDEF(LmsNetAttributes);

    class LmsNeuronAttributes : public Attributes
    {
    public:
        LmsNeuronAttributes() : localGradient(0), error(0) {};
        virtual ~LmsNeuronAttributes() {};

        static const HashType getHash()
        {
            static HashType groupName = hash("LmsNetAttributes");
            return groupName;
        };

    public:
        Float localGradient;
        Float error;
        LmsNetAttributesPtr parent;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<LmsNeuronAttributes, Attributes>(
                    static_cast<LmsNeuronAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(localGradient)
                & BOOST_SERIALIZATION_NVP(error);
            };

    }; //LmsNeuronAttributes

    class LmsLinkAttributes : public Attributes
    {
    public:
        LmsLinkAttributes() : lastDeltaW(0) {};
        virtual ~LmsLinkAttributes() {};

        static const HashType getHash()
        {
            static HashType groupName = hash("LmsNetAttributes");
            return groupName;
        };

    public:
        Float lastDeltaW;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<LmsLinkAttributes, Attributes>(
                    static_cast<LmsLinkAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(lastDeltaW);
            };

    }; //LmsLinkAttributes

}; //pann

REGISTER_ATTRIBUTES(LmsNetAttributes);
REGISTER_ATTRIBUTES(LmsNeuronAttributes);
REGISTER_ATTRIBUTES(LmsLinkAttributes);

#endif

