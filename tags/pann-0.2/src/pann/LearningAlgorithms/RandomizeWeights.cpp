//RandomizeWeights.cpp

#include "Includes/BoostSerialization.h"
#include "RandomizeWeights.h"

REGISTER_SINGLETON_CPP(RandomizeWeightsGaussRunner);
REGISTER_SINGLETON_CPP(RandomizeWeightsAccordingToInputsCountRunner);
REGISTER_ATTRIBUTES_CPP(WeightRandomizationAttributes);

#include "Core/Random.h"
#include "Core/Neuron.h"
#include "Core/Net.h"

namespace pann
{
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
            _neuron->getBias()->setValue(rand(attrs.min, attrs.max));

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron->getInConnections())
            link.getWeight()->setValue(rand(attrs.min, attrs.max));
    } //run

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
            _neuron->getBias()->setValue(rand(attrs.min, attrs.max) / C);

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron->getInConnections())
            link.getWeight()->setValue(rand(attrs.min, attrs.max) / C);
    } //run

}; //pann

