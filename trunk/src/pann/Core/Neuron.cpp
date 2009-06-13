//Neuron.cpp

#include "Neuron.h"
#include "Runner.h"
#include "Weight.h"

namespace pann
{
    void
    Neuron::setInput(Float _value)
    {
        receptiveField = _value;
    } //setInput

    Float
    Neuron::getReceptiveField() const
    {
        return receptiveField;
    } //getReceptiveField

    Float
    Neuron::getOutput() const
    {
        return activationValue;
    } //getOutput

    list<Link>&
    Neuron::getInConnections()
    {
        return links_in;
    } //getInConnections

    list<Link>&
    Neuron::getOutConnections()
    {
        return links_out;
    } //getOutConnections

    const WeightPtr&
    Neuron::getBias() const
    {
        return bias;
    } //getBias

    const ActivationFunctionPtr&
    Neuron::getActivationFunction()
    {
        return activationFunction;
    } //getActivationFunction

    const RunnerPtr&
    Neuron::getFireRunner() const
    {
        return fireRunner;
    } //getFireRunner

    const RunnerPtr&
    Neuron::getLearnRunner() const
    {
        return learnRunner;
    } //getLearnRunner

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

    void
    Neuron::setBias(WeightPtr _bias)
    {
        if(bias)
        {
            bias->decUsageCount();
            bias->decUsageCount();
        }
        bias = _bias;
        if(bias)
        {
            bias->incUsageCount();
            bias->incUsageCount();
        }
    } //setBias

    void
    Neuron::setActivationFunction(ActivationFunctionPtr _af)
    {
        activationFunction = _af;
    } //setActivationFunction

    void
    Neuron::setFireRunner(RunnerPtr _runner)
    {
        if(ForwardRun != _runner->getDirection())
            throw Exception()<<"Neuron::setFireRunner(): Wrong direction\n";

        fireRunner = _runner;
    } //setFireRunner

    void
    Neuron::setLearnRunner(RunnerPtr _runner)
    {
        //Learning may be in forward direction too, so we don't check _runner direction
        learnRunner = _runner;
    } //setLearnRunner

}; //pann
