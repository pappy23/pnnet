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
        Attributes& neuron_hint = _neuron->learningHint; //Parametrs specific to current neuron
        const Attributes& net_hint = _net->learningHint; //Global learning parameters

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
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons)

        //Save actual local gradient value
        //Note: we assume that input neuron has activation function y=x, so y'=1
        if(_neuron->getActivationFunction()) 
            neuron_hint[localGradient] *= _neuron->getActivationFunction()->derivative_dy(_neuron->activationValue);
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)
        
        //Update weights
        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::out);
            {
                //TODO: shared weights
                Weight* w = const_cast<Weight*>(link.getWeight());

                if(!w->learningHint.is(LMS))
                {
                    w->learningHint.erase();
                    w->learningHint[LMS] = 1.0;
                }

                //See Haykin, p241
                Float dw = net_hint[learningMomentum] * w->learningHint[lastDeltaW]
                    + net_hint[learningRate] * neuron_hint[localGradient] * _neuron->activationValue;

                w->learningHint[lastDeltaW] = dw;

                w->value += dw;

            }
        }
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection() throw()
    {
        return BackwardRun;
    } //getDirection

}; //pann

