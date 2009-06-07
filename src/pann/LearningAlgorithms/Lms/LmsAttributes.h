#ifndef LMSATTRIBUTES_H
#define LMSATTRIBUTES_H

#include "Core/Attributes.h"

namespace pann
{
    namespace AttributesGroup
    {
        const HashType LmsNet    = hash("LmsNetAttributes");
        const HashType LmsNeuron = hash("LmsNeuronAttributes");
        //const HashType LmsLink   = hash("LmsLinkAttributes");
        const HashType LmsWeight = hash("LmsWeightAttributes");
    }; //AttributesGroup

    ADD_PTR_TYPEDEF(LmsNetAttributes);
    ADD_PTR_TYPEDEF(LmsNeuronAttributes);
    //ADD_PTR_TYPEDEF(LmsLinkAttributes);
    ADD_PTR_TYPEDEF(LmsWeightAttributes);

    class LmsNetAttributes : public Attributes
    {
    public:
        LmsNetAttributes() {};
        virtual ~LmsNetAttributes() {};

        virtual HashType getName() { return AttributesGroup::LmsNet; };

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

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Attributes)
                   & BOOST_SERIALIZATION_NVP(learningRate)
                   & BOOST_SERIALIZATION_NVP(learningMomentum)
                   & BOOST_SERIALIZATION_NVP(epoch)
                   & BOOST_SERIALIZATION_NVP(annealingTSC);
            };
    }; //LmsNetAttributes

    class LmsNeuronAttributes : public Attributes
    {
    public:
        LmsNeuronAttributes() {};
        virtual ~LmsNeuronAttributes() {};

        virtual HashType getName() { return AttributesGroup::LmsNeuron; };

        Float error;
        Float localGradient;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<LmsNeuronAttributes, Attributes>(
                    static_cast<LmsNeuronAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Attributes)
                   & BOOST_SERIALIZATION_NVP(error)
                   & BOOST_SERIALIZATION_NVP(localGradient);
            };
    }; //LmsNeuronAttributes
/*
    class LmsLinkAttributes : public Attributes
    {
    public:
        LmsLinkAttributes() {};
        virtual ~LmsLinkAttributes() {};

        virtual HashType getName() { return AttributesGroup::LmsLink; };
        virtual const char* getAlgorithmName() = 0;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<LmsLinkAttributes, Attributes>(
                    static_cast<LmsLinkAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Attributes);
            };
    }; //LmsLinkAttributes
*/
    class LmsWeightAttributes : public Attributes
    {
    public:
        LmsWeightAttributes() {};
        virtual ~LmsWeightAttributes() {};

        virtual HashType getName() { return AttributesGroup::LmsWeight; };

        Float lastDeltaW;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<LmsWeightAttributes, Attributes>(
                    static_cast<LmsWeightAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Attributes)
                   & BOOST_SERIALIZATION_NVP(lastDeltaW);
            };
    }; //LmsWeightAttributes

}; //pann

#endif

