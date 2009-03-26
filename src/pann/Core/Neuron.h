//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"
#include "Attributes.h"

namespace pann
{
    class Neuron : public Object
    {
        /* Private attributes */
    private:
        ActivationFunction::Base* activationFunction;

        /**
         * Thread with this number will take care of our Neuron
         */
        unsigned ownerThread;

        /* Public attributes
         * Note: Neuron is usually hidden by Net,
         * so there is nothing to worry about
         */
    public:
        Float receptiveField;
        Float activationValue;
        std::list<Link> links; //!< List of Link, both directions
        Attributes oglHint;
        Attributes learningHint;
    
        /* Public interface */
    public:
        Neuron();
        Neuron(ActivationFunction::Base*);
        ~Neuron();

        void setOwnerThread(unsigned _thread);
        unsigned getOwnerThread() const;

        const ActivationFunction::Base* getActivationFunction() const;

        /**
         * Helper. Finds and returns Link* for Neuron _to
         */
        std::list<Link>::iterator findLink(Neuron* _to, Link::Direction _direction);

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(ownerThread)
                 & BOOST_SERIALIZATION_NVP(receptiveField)
                 & BOOST_SERIALIZATION_NVP(activationValue)
                 & BOOST_SERIALIZATION_NVP(oglHint)
                 & BOOST_SERIALIZATION_NVP(learningHint)
                 & BOOST_SERIALIZATION_NVP(links)
                 & BOOST_SERIALIZATION_NVP(activationFunction);
            };
    };

}; //pann

#endif //NEURON_H

