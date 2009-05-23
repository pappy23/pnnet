//Neuron.cpp

#include "Neuron.h"

using namespace std;
using namespace boost;

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base* _activationFunction, shared_ptr<Weight> _bias)
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
            throw E<Exception::ObjectNotFound>()<<"Neuron::getActivationFunction(): No activation function!\n";

        return *activationFunction;
    } //getOwnerThread

    void
    Neuron::addInConnection(shared_ptr<Neuron> _to, shared_ptr<Weight> _weight)
    {
        delConnection(_to);
        links_in.push_back( Link(_to, _weight) );
    } //addInConnection
    
    void
    Neuron::addOutConnection(shared_ptr<Neuron> _to, shared_ptr<Weight> _weight)
    { 
        delConnection(_to);
        links_out.push_back( Link(_to, _weight) );
    } //addOutConnection
    
    void
    Neuron::delConnection(shared_ptr<Neuron> _to)
    {
        //TODO
//        links_in.remove_if(boost::lambda::bind(&is_equal(), _to ->* get, _2)(bind()));
//        links_in.remove_if(bind(is_equal, _to ->* &shared_ptr<Neuron>::get)(& _1 ->* &Link::getTo));
        //links_out.remove_if(bind(is_equal(), &(X ->* &Link::getTo), _to.get()));
    } //delConnection

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

    Weight&
    Neuron::getBias()
    {
        if(!bias)
            throw E<Exception::ObjectNotFound>()<<"Link::getBias(): No bias\n";

        return *bias;
    } //getBias

    const Weight&
    Neuron::getBias() const
    {
        if(!bias)
            throw E<Exception::ObjectNotFound>()<<"Link::getBias(): No bias\n";

        return *bias;
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
