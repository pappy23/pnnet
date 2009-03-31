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

        /* Public attributes */
    public:
        Float activationValue;
        std::list<Link> links; //!< List of Link, both directions
        Weight* bias;
        Attributes oglHint;
        Attributes learningHint;
    
        /* Public interface */
    public:
        Neuron(ActivationFunction::Base*) throw();
        virtual ~Neuron() throw();

        const ActivationFunction::Base* getActivationFunction() const throw();

        /**
         * Helper. Finds and returns Link* for Neuron _to
         */
        std::list<Link>::iterator findLink(Neuron* _to, Link::Direction _direction) 
            throw(E<Exception::MultipleOccurance>, E<Exception::ObjectNotFound>);

        /* Serialization */
    private:
        Neuron() throw() {};
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ActivationFunction::boost_export();

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(activationFunction)
                 & BOOST_SERIALIZATION_NVP(activationValue)
                 & BOOST_SERIALIZATION_NVP(links)
                 & BOOST_SERIALIZATION_NVP(bias)
                 & BOOST_SERIALIZATION_NVP(oglHint)
                 & BOOST_SERIALIZATION_NVP(learningHint);
            };
    };

}; //pann

#endif //NEURON_H

