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

    Runner&
    LmsFeedforwardRunner::Instance() throw()
    {
        if(!self)
            self = new LmsFeedforwardRunner();

        return *self;
    } //Instance

    void
    LmsFeedforwardRunner::run(Neuron& _neuron, const Net& _net) throw()
    {
        if(_neuron.is(LMS))
        {
            _neuron.erase(AlgorithmSpecificLearningParameters);
            _neuron[LMS] = 1.0;
        }

        //Usually we don't need to do anything with input neurons, but lastReceptiveField
        //is required by LMS even for them
        if(!_neuron.hasActivationFunction())
        {
            _neuron[lastReceptiveField] = _neuron[Neuron::activationValue];
            return;
        }

        Float receptiveField = 0;
        if(_neuron.hasBias())
            receptiveField += _neuron.getBias()[Weight::value];

        BOOST_FOREACH( Link& link, _neuron.links )
        {
            if(link.getDirection() == Link::in)
                receptiveField += link.getTo()[Neuron::activationValue] * link.getWeight()[Weight::value];
        }

        _neuron[activationValue] = _neuron.getActivationFunction().f(receptiveField);
        _neuron[lastReceptiveField] = receptiveField;
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
    
    Runner&
    LmsBackpropagationRunner::Instance() throw()
    {
        if(!self)
            self = new LmsBackpropagationRunner();

        return *self;
    } //Instance

    void
    LmsBackpropagationRunner::run(Neuron& _neuron, const Net& _net) throw(E<Exception::NotReady>)
    {
        if(!_neuron.is(LMS))
            throw E<Exception::NotReady>()<<"LmsBackpropagationRunner::run(): Feedforward run wasn't made\n";

        //local_gradient = desired_output - actual_output = error - for output neuron
        //local_gradient = weighted sum of upstream neurons local_gradients
        if(_neuron.is(error)) //output neuron
            _neuron[localGradient] = _neuron[error];
        else
            _neuron[localGradient] = 0;

        BOOST_FOREACH( Link& link, _neuron.links )
            if(link.getDirection() == Link::out)
                _neuron[localGradient] += link.getTo()[localGradient] * link.getWeight[value];
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons for other layers)

        //Save actual local gradient value
        //Note: we assume that input neuron(it's activation function = 0) 
        //has activation function y = x, so dy/dx = 1
        if(_neuron.hasActivationFunction()) 
            _neuron[localGradient] *= _neuron.getActivationFunction().derivative_dy(_neuron[Neuron::activationValue]);
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)
        
        //Update weights
        //Comment: Na --w--> Nb
        //w is updated while processing Na
        BOOST_FOREACH( Link& link, _neuron.links )
        {
            if(link.getDirection() == Link::out)
            {
                //TODO: shared weights
                Weight& w = link.getWeight();
                boost::mutex::scoped_lock lock(w.mutex);

                if(!w.is(LMS))
                {
                    w.erase(AlgorithmSpecificLearningParameters);
                    w[LMS] = 1.0;
                }

                //See Haykin, p241
                //Ni -> Nj
                //dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
                Float dw = _net[learningRate] * link.getTo()[localGradient] * _neuron[Neuron::activationValue];
                
                if(w.usageCount == 2)
                {
                    //Currently there is no way to make lastDeltaW thread safe
                    dw += _net[learningMomentum] * w[lastDeltaW];
                    w[lastDeltaW] = dw;
                }

                w[Weight::value] += dw * 2.0 / (Float)w.usageCount;
            }
        }

        //Update bias weight
        if(_neuron.hasBias())
        {
            Weight& w = _neuron.getBias();

            if(!w.is(LMS))
            {
                w.erase(AlgorithmSpecificLearningParameters);
                w[LMS] = 1.0;
            }

            Float dw = _net[learningMomentum] * w[lastDeltaW]
                + _net[learningRate] * _neuron[localGradient];

            w[lastDeltaW] = dw;

            w[Weight::value] += dw;
        }
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection() throw()
    {
        return BackwardRun;
    } //getDirection

}; //pann

