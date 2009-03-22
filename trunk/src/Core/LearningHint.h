#ifndef LEARNINGHINT_H
#define LEARNINGHINT_H

#include "Includes.h"
#include "Exception.h"

namespace pann
{
    namespace LearningHint
    {
        /**
         * Learning hint is attache to Net or Neuron and used by learning algorithms
         * to store some algorithm-specific data
         * Each algorithm checks whether Net and Neuron hints were created by him
         */

        enum HintId
        {
            NullId = 1,
            LmsNetId = 2,
            LmsNeuronId = 3
        };

        /**
         * Base class for both learning hints - Net and Neuron
         */
        class Base
        {
        public:
            Base() { };
            virtual ~Base() { };

            virtual HintId getTypeId() = 0;

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    //Do nothing in base class
                };
        };

        /**
         * Empty hint. Used for testing
         */
        class Null
        {
        public:
            Null() { };
            virtual ~Null() { };

            virtual HintId getTypeId()
            {
                return NullId;
            };

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    //Do nothing
                };
        };

        class LmsNet : public Base
        {
            /* Public members */
        public:
            Float learningRate;

            /* Public interface */
        public:
            LmsNet() : learningRate(0) { };
            virtual ~LmsNet() { };

            virtual HintId getTypeId()
            {
                return LmsNetId;
            }

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    ar & learningRate;
                };
        };

        class LmsNeuron : public Base
        {
            /* Public interface */
        public:
            LmsNeuron() { };
            virtual ~LmsNeuron() { };

            virtual HintId getTypeId()
            {
                return LmsNeuronId;
            }

            /* Private members */
        private:
            //Float learningRate;

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
              //      ar & learningRate;
                };
        };

        /**
         * getById() is used for serialization
         */
        inline Base* getById(HintId _id)
        {
            switch(_id)
            {
            case NullId:
                return (Base*)new Null;
                break;
            case LmsNetId:
                return (Base*)new LmsNet;
                break;
            case LmsNeuronId:
                return (Base*)new LmsNeuron;
                break;
            default:
                throw Exception::ObjectNotFound()<<"LearningHint::getById(): unknown hint id: "<<_id<<"\n";
            }
        } //getById
    };

}; //pann

#endif

