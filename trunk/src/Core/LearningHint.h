#ifndef LEARNINGHINT_H
#define LEARNINGHINT_H

#include "Includes.h"
#include "Exception.h"

namespace pann
{
    namespace LearningHint
    {
        /**
         * Learning hint is attached to Net or Neuron and used by learning algorithms
         * to store some algorithm-specific data
         * Each algorithm checks whether Net and Neuron hints were created by him
         */

        /**
         * Base class for both learning hints - Net and Neuron
         */
        class Base
        {
        public:
            Base() { };
            virtual ~Base() { };

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                };
        };

    };

}; //pann

//BOOST_IS_ABSTRACT(pann::LearningHint::Base)

#endif

