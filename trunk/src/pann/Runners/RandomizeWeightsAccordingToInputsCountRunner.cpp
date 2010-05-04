//RandomizeWeightsAccordingToInputsCountRunner.cpp

#include "RandomizeWeightsAccordingToInputsCountRunner.h"

REGISTER_SINGLETON_CPP(RandomizeWeightsAccordingToInputsCountRunner);

#include "Core/Net.h"
#include "Core/Random.h"
#include "Attributes/WeightRandomizationAttributes.h"

namespace pann {
    void
    RandomizeWeightsAccordingToInputsCountRunner::run(NeuronPtr _neuron, Net* _net) const
    {
        WeightRandomizationAttributes& attrs = _net->get<WeightRandomizationAttributes>();
        if(attrs.min == 0 && attrs.max == 0)
        {
            attrs.min = -2.4;
            attrs.max = +2.4;
        }

        Float C = sqrt(Float(_neuron->getInConnections().size()));
        if(C == 0)
            C = 10.0;

        //Tune bias values
        if(_neuron->getBias())
            _neuron->getBias()->addValue(pann::rand(attrs.min, attrs.max) / C - _neuron->getBias()->getValue());

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron->getInConnections())
            link.getWeight()->addValue(pann::rand(attrs.min, attrs.max) / C - link.getWeight()->getValue());
    } //run

}; //pann
