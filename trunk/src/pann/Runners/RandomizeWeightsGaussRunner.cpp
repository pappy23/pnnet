//RandomizeWeightsGaussRunner.cpp

#include "RandomizeWeightsGaussRunner.h"

REGISTER_SINGLETON_CPP(RandomizeWeightsGaussRunner);

#include "Core/Net.h"
#include "Core/Random.h"
#include "Attributes/WeightRandomizationAttributes.h"

namespace pann {
    void
    RandomizeWeightsGaussRunner::run(ObjectPtr net, NeuronPtr neuron) const
    {
        //Tune bias values
        if(neuron->bias)
            neuron->bias->addValue(pann::rand(attrs.min, attrs.max) - _neuron->getBias()->getValue());

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron->getInConnections())
            link.getWeight()->addValue(pann::rand(attrs.min, attrs.max) - link.getWeight()->getValue() );
    } //run

}; //pann
