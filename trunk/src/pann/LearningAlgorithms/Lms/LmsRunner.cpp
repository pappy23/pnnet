//LmsRunner.cpp

#include "LmsRunner.h"

using namespace pann::LmsAttributes;
using namespace pann::AttributesDeclaration;

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
        AttributesManager neuron_attrs(_neuron);

        if(!neuron_attrs.is(LMS))
        {
            neuron_attrs.erase(AlgorithmSpecificLearningParameters);
            neuron_attrs[LMS] = 1.0;
        }

        //Usually we don't need to do anything with input neurons, but lastReceptiveField
        //is required by LMS even for them
        if(!_neuron->getActivationFunction())
        {
            neuron_attrs[lastReceptiveField] = _neuron->activationValue;
            return;
        }

        Float receptiveField = 0;
        if(_neuron->bias)
            receptiveField += _neuron->bias->value;

        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::in)
                receptiveField += link.getTo()->activationValue * link.weight->value;
        }

        _neuron->activationValue = _neuron->getActivationFunction()->f(receptiveField);
        neuron_attrs[lastReceptiveField] = receptiveField;
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
        AttributesManager neuron_hint(_neuron, _net);

        if(!neuron_hint.is(LMS))
            throw E<Exception::NotReady>()<<"LmsBackpropagationRunner::run(): Feedforward run wasn't made\n";

        //local_gradient = desired_output - actual_output = error - for output neuron
        //local_gradient = weighted sum of upstream neurons local_gradients
        if(neuron_hint.is(error)) //output neuron
            neuron_hint[localGradient] = neuron_hint[error];
        else
            neuron_hint[localGradient] = 0;

        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::out)
            {
                AttributesManager to_neuron_hint(link.getTo());
                neuron_hint[localGradient] += to_neuron_hint[localGradient] * link.weight->value;
            }
        }
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons for other layers)

        //Save actual local gradient value
        //Note: we assume that input neuron(it's activation function = 0) 
        //has activation function y = x, so dy/dx = 1
        if(_neuron->getActivationFunction()) 
            neuron_hint[localGradient] *= _neuron->getActivationFunction()->derivative_dy(_neuron->activationValue);
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)
        
        //Update weights
        //Comment: Na --w--> Nb
        //w is updated while processing Na
        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::out)
            {
                //TODO: shared weights
                Weight* w = link.weight;
                AttributesManager w_hint(w, _neuron, _net);
                boost::mutex::scoped_lock lock(w->mutex);

                if(!w_hint.is(LMS))
                {
                    w_hint.erase(AlgorithmSpecificLearningParameters);
                    w_hint[LMS] = 1.0;
                }

                //See Haykin, p241
                //Ni -> Nj
                //dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
                Float dw = w_hint[learningRate] * AttributesManager(link.getTo())[localGradient] * _neuron->activationValue;
                
                if(w->usageCount == 2)
                {
                    //Currently there is no way to make lastDeltaW thread safe
                    dw += w_hint[learningMomentum] * w_hint[lastDeltaW];
                    w_hint[lastDeltaW] = dw;
                }

                w->value += dw * 2.0 / (Float)w->usageCount;
            }
        }

        //Update bias weight
        if(_neuron->bias)
        {
            Weight* w = _neuron->bias;
            AttributesManager w_hint(w, _neuron, _net);

            if(!w_hint.is(LMS))
            {
                w_hint.erase(AlgorithmSpecificLearningParameters);
                w_hint[LMS] = 1.0;
            }

            Float dw = w_hint[learningMomentum] * w_hint[lastDeltaW]
                + w_hint[learningRate] * neuron_hint[localGradient];

            w_hint[lastDeltaW] = dw;

            w->value += dw;
        }
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection() throw()
    {
        return BackwardRun;
    } //getDirection

}; //pann

