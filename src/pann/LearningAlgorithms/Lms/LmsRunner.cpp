//LmsRunner.cpp

#include "LmsRunner.h"

using namespace pann::LmsAttributes;

namespace pann
{
    Runner* LmsFeedforwardRunner::self = 0;
    Runner* LmsBackpropagationRunner::self = 0;

    LmsFeedforwardRunner::LmsFeedforwardRunner() throw()
    {
    } //LmsFeedforwardRunner

    LmsFeedforwardRunner::~LmsFeedforwardRunner() throw()
    {
    } //~LmsFeedforwardRunner

    Runner*
    LmsFeedforwardRunner::Instance() throw()
    {
        if(!self)
            self = new LmsFeedforwardRunner();

        return self;
    } //Instance

    void
    LmsFeedforwardRunner::run(Neuron* _neuron, const Net* _net) throw()
    {
        if(!_neuron->learningHint.is(LMS))
        {
            _neuron->learningHint.erase();
            _neuron->learningHint[LMS] = 1.0;
        }

        if(!_neuron->getActivationFunction())
        {
            _neuron->learningHint[lastReceptiveField] = _neuron->activationValue;
            return;
        }

        Float receptiveField = 0;

        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::in)
                receptiveField += link.getTo()->activationValue * link.getWeight()->value;
        }

        _neuron->activationValue = _neuron->getActivationFunction()->f(receptiveField);
        _neuron->learningHint[lastReceptiveField] = receptiveField;
    } //run

    RunDirection
    LmsFeedforwardRunner::getDirection() throw()
    {
        return ForwardRun;
    } //getDirection

    LmsBackpropagationRunner::LmsBackpropagationRunner() throw()
    {
    } //LmsBackpropagationRunner

    LmsBackpropagationRunner::~LmsBackpropagationRunner() throw()
    {
    } //~LmsBackpropagationRunner
    
    Runner* 
    LmsBackpropagationRunner::Instance() throw()
    {
        if(!self)
            self = new LmsBackpropagationRunner();

        return self;
    } //Instance

    void
    LmsBackpropagationRunner::run(Neuron* _neuron, const Net* _net) throw(E<Exception::NotReady>)
    {
        Attributes& neuron_hint = _neuron->learningHint;
        const Attributes& net_hint = _net->learningHint;

        if(!neuron_hint.is(LMS))
            throw E<Exception::NotReady>()<<"LmsBackpropagationRunner::run(): Feedforward run wasn't made\n";

        //Accumulate error value in [localGradient]
        if(neuron_hint.is(error))
            neuron_hint[localGradient] = neuron_hint[error];
        else
            neuron_hint[localGradient] = 0;

        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::out)
                neuron_hint[localGradient] += 
                    link.getTo()->learningHint[localGradient] * link.getWeight()->value;
        }

        //Save actual local gradient value
        //Note: we assume that input neuron has activation function y=x, so y'=1
        if(_neuron->getActivationFunction()) 
            neuron_hint[localGradient] *= _neuron->getActivationFunction()->derivative(neuron_hint[lastReceptiveField]);
        
        //Update weights
        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::out);
            {
                Weight* w = const_cast<Weight*>(link.getWeight());

                if(!w->learningHint.is(LMS))
                {
                    w->learningHint.erase();
                    w->learningHint[LMS] = 1.0;
                }

                Float dw = net_hint[learningMomentum] * w->learningHint[lastDeltaW]
                    + net_hint[learningRate] * neuron_hint[localGradient] * _neuron->activationValue;

                w->learningHint[lastDeltaW] = dw;

                w->value += dw;

//            dw = a * prev_dw + lrate * localGradient * activationValue; 
            }
        }
        
                std::cout<<"1";
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection() throw()
    {
        return BackwardRun;
    } //getDirection

}; //pann

