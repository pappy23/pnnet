//Neuron.cpp

#include "Neuron.h"

using namespace std;
using namespace boost;

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base* _activationFunction, WeightPtr _bias)
        : activationFunction(_activationFunction), bias(_bias)
    {
        if(activationFunction)
            fire();
        else
            receptiveField = activationValue = 0;

        if(bias)
        {
            bias->incUsageCount();
            bias->incUsageCount();
        }
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    Float
    Neuron::getReceptiveField() const
    {
        return receptiveField;
    } //getReceptiveField

    Float
    Neuron::getActivationValue() const
    {
        return activationValue;
    } //getActivationValue

    void
    Neuron::setInput(Float _value)
    {
        receptiveField = _value;
    } //setInput

    const ActivationFunction::Base&
    Neuron::getActivationFunction() const
    {
        if(!activationFunction)
            throw NotFound()<<"Neuron::getActivationFunction(): No activation function!\n";

        return *activationFunction;
    } //getOwnerThread

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
        //TODO: Fix this shit. Or not?
        struct comparator
        {
            static bool comp(NeuronPtr _to, const Link& _l)
            {
                return _l.getTo() == _to;
            }
        };

        links_out.remove_if(bind(comparator::comp, _to, _1));
    } //delOutConnection

    const std::list<Link>&
    Neuron::getInConnections() const
    {
        return links_in;
    } //getInConnections

    const std::list<Link>&
    Neuron::getOutConnections() const
    {
        return links_out;
    } //getOutConnections

    bool
    Neuron::hasBias() const
    {
        if(bias)
            return true;

        return false;
    } //hasBias

    WeightPtr
    Neuron::getBias()
    {
        if(!bias)
            throw NotFound()<<"Link::getBias(): No bias\n";

        return bias;
    } //getBias

    const WeightPtr
    Neuron::getBias() const
    {
        if(!bias)
            throw NotFound()<<"Link::getBias(): No bias\n";

        return bias;
    } //getBias

    void
    Neuron::fire()
    {
        if(bias)
            receptiveField += bias->getValue();

        BOOST_FOREACH( Link& link, links_in )
            receptiveField += link.getTo()->getActivationValue() * link.getWeight()->getValue();

        activationValue = activationFunction->f(receptiveField);
        receptiveField = 0;
    } //fire

}; //pann
