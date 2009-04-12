//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"

namespace pann
{
    class Neuron : public Object
    {
        /* Attributes */
    public:
        static const AttributeName activationValue;

        /* Private attributes */
    private:
        ActivationFunction::Base* activationFunction;
        Weight* bias;

        /* Public attributes */
    public:
        //TODO: make links private to prevent user from modifying connections
        std::list<Link> links; //!< List of Link, both directions
    
        /* Public interface */
    public:
        Neuron(ActivationFunction::Base*, Weight* _bias = 0) throw();
        virtual ~Neuron() throw();

        bool hasActivationFunction() const throw();
        const ActivationFunction::Base& getActivationFunction() const throw(E<Exception::ObjectNotFound>);

        bool hasBias() const throw();
        Weight& getBias() throw(E<Exception::ObjectNotFound>);
        const Weight& getBias() const throw(E<Exception::ObjectNotFound>);

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
                 & BOOST_SERIALIZATION_NVP(links)
                 & BOOST_SERIALIZATION_NVP(bias);
            };
    };

}; //pann

#endif //NEURON_H

