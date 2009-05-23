//RandomizeWeights.cpp

#include "Core/Random.h"
#include "RandomizeWeights.h"

using namespace pann::RandomizeWeightsAttributes;

namespace pann
{             
    Runner* RandomizeWeightsGaussRunner::self = 0;

    void
    RandomizeWeightsGaussRunner::run(Neuron& _neuron, const Net& _net)
    {
        //Tune bias values
        if(_neuron.hasBias())
            _neuron.getBias()->setValue(rand(_net[min], _net[max]));

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron.getInConnections())
            link.getWeight()->setValue(rand(_net[min], _net[max]));
    } //run

    Runner* RandomizeWeightsAccordingToInputsCountRunner::self = 0;

    void
    RandomizeWeightsAccordingToInputsCountRunner::run(Neuron& _neuron, const Net& _net)
    {
        /*
        if(!_net.is(min))
            _net[min] = -2.4;
        if(!_net.is(max))
            _net[max] = +2.4;
        */

        Float C = sqrt(Float(_neuron.getInConnections().size()));
        if(C == 0)
            C = 10.0;

        //Tune bias values
        if(_neuron.hasBias())
            _neuron.getBias()->setValue(rand(_net[min], _net[max]) / C);

        //Link weights
        BOOST_FOREACH(const Link& link, _neuron.getInConnections())
            link.getWeight()->setValue(rand(_net[min], _net[max]) / C);
    } //run

}; //pann

