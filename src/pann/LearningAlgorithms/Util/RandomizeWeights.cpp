//RandomizeWeights.cpp

#include "Core/Random.h"
#include "RandomizeWeights.h"

using namespace pann::AttributesGroup;

namespace pann
{
    Runner* RandomizeWeightsGaussRunner::self = 0;

    void
    RandomizeWeightsGaussRunner::run(Neuron& _neuron, const Net& _net)
    {
        WeightsRandomizationAttributesPtr param = _net.at<WeightsRandomizationAttributes>(WeightsRandomization);
        if(!param)
        {
            param.reset(new WeightsRandomizationAttributes());
            param->min() = -0.3;
            param->max() = +0.3;
        }

        //Tune bias values
        if(_neuron.hasBias())
            _neuron.getBias()->setValue(rand(param->min(), param->max()));

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron.getInConnections())
            link.getWeight()->setValue(rand(param->min(), param->max()));
    } //run

    Runner* RandomizeWeightsAccordingToInputsCountRunner::self = 0;

    void
    RandomizeWeightsAccordingToInputsCountRunner::run(Neuron& _neuron, const Net& _net)
    {
        WeightsRandomizationAttributesPtr param = _net.at<WeightsRandomizationAttributes>(WeightsRandomization);
        if(!param)
        {
            param.reset(new WeightsRandomizationAttributes());
            param->min() = -2.4;
            param->max() = +2.4;
        }

        Float C = sqrt(Float(_neuron.getInConnections().size()));
        if(C == 0)
            C = 10.0;

        //Tune bias values
        if(_neuron.hasBias())
            _neuron.getBias()->setValue(rand(param->min(), param->max()) / C);

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron.getInConnections())
            link.getWeight()->setValue(rand(param->min(), param->max()) / C);
    } //run

}; //pann

