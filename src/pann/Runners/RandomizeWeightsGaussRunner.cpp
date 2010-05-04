//RandomizeWeightsGaussRunner.cpp

#include "RandomizeWeightsGaussRunner.h"

REGISTER_SINGLETON_CPP(RandomizeWeightsGaussRunner);

#include "Core/Net.h"
#include "Core/Random.h"
#include "Attributes/WeightRandomizationAttributes.h"

namespace pann {
    void
    RandomizeWeightsGaussRunner::run(NeuronPtr _neuron, Net* _net) const
    {
        WeightRandomizationAttributes& attrs = _net->get<WeightRandomizationAttributes>();
        if(attrs.min == 0 && attrs.max == 0)
        {
            attrs.min = -0.3;
            attrs.max = +0.3;
        }

        //Tune bias values
        if(_neuron->getBias())
            _neuron->getBias()->addValue(pann::rand(attrs.min, attrs.max) - _neuron->getBias()->getValue());

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron->getInConnections())
            link.getWeight()->addValue(pann::rand(attrs.min, attrs.max) - link.getWeight()->getValue() );
    } //run

}; //pann
