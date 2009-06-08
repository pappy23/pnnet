//Neuron.cpp

#include "Neuron.h"

using namespace std;
using namespace boost;

namespace pann
{
    void
    Neuron::addInConnection(NeuronPtr _to, WeightPtr _weight)
    {
        links_in.push_back( Link(_to, _weight) );
    } //addInConnection

    void
    Neuron::addOutConnection(NeuronPtr _to, WeightPtr _weight)
    {
        links_out.push_back( Link(_to, _weight) );
    } //addOutConnection

    void
    Neuron::delInConnection(NeuronPtr _to)
    {
        //TODO: Fix this shit. Or not?
        struct comparator
        {
            static bool comp(NeuronPtr _to, const Link& _l)
            {
                return _l.getTo() == _to;
            }
        };

        links_in.remove_if(bind(comparator::comp, _to, _1));
    } //delInConnection

    void
    Neuron::delOutConnection(NeuronPtr _to)
    {
        struct comparator
        {
            static bool comp(NeuronPtr _to, const Link& _l)
            {
                return _l.getTo() == _to;
            }
        };

        links_out.remove_if(bind(comparator::comp, _to, _1));
    } //delOutConnection
/*
    void
    PyramidalNeuron::fire()
    {
        if(bias)
            receptiveField += bias->getValue();

        BOOST_FOREACH( const Link& link, links_in )
            receptiveField += link.getTo()->getOutput() * link.getWeight()->getValue();

        activationValue = 0;
        if(activationFunction)
            activationValue += activationFunction->f(receptiveField);

        receptiveField = 0;
    } //fire

    void
    PyramidalNeuron::learn()
    {
    } //learn
*/
}; //pann
