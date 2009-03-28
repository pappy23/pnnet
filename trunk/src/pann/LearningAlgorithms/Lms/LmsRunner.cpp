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
    LmsFeedforwardRunner::run(Neuron* _neuron) throw()
    {
        if(!_neuron->learningHint.is(LMS))
        {
            _neuron->learningHint.erase();
            _neuron->learningHint[LMS] = 1.0;
        }

        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::in)
                _neuron->receptiveField += link.getTo()->activationValue * link.getWeight()->value;
        }

        _neuron->activationValue = _neuron->getActivationFunction()->f(_neuron->receptiveField);
        _neuron->learningHint[lastReceptiveField] = _neuron->receptiveField;
        _neuron->receptiveField = 0;
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
    LmsBackpropagationRunner::run(Neuron* _neuron) throw(E<Exception::NotReady>)
    {
        Attributes& neuron_hint = _neuron->learningHint;

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

        //_neuron->activationValue = _neuron->getActivationFunction()->f(_neuron->receptiveField);
        
        //Save actual local gradient value
        neuron_hint[localGradient] = 
            neuron_hint[localGradient] * _neuron->getActivationFunction()->derivative(neuron_hint[lastReceptiveField]);
        
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

                //TODO decide how to organize access from Runner to network attributes
                Float dw = neuron_hint[learningMomentum] * w->learningHint[lastDeltaW] 
                    + net.learningHint[learningRate] * neuron_hint[localGradient] * _neuron->activationValue;

//            dw = a * prev_dw + lrate * localGradient * activationValue; 
            }
        }
        
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection() throw()
    {
        return BackwardRun;
    } //getDirection

}; //pann

