//RandomizeWeightsGauss.cpp

#include "RandomizeWeightsGauss.h"

REGISTER_SINGLETON_CPP(RandomizeWeightsGaussRunner);

#include "Core/Random.h"

namespace pann {
    void
    RandomizeWeightsGaussRunner::run(ObjectConstPtr net, NeuronPtr neuron) const
    {
        Float min = net->get_attr(hash("RW_MIN"));
        Float max = net->get_attr(hash("RW_MAX"));

        //Tune bias values
        if(neuron->bias)
            neuron->bias->add_value(pann::rand(min, max) - neuron->bias->get_value());

        //Link weights
        BOOST_FOREACH(const Link& link, neuron->input_links)
            link.get_weight()->add_value(pann::rand(min, max) - link.get_weight()->get_value() );
    }; //run

    void
    randomize_weights_gauss(NetPtr net, Float min, Float max)
    {
        net->set_attr(hash("RW_MIN"), min);
        net->set_attr(hash("RW_MAX"), max);
        net->run(Net::ForwardRun, RandomizeWeightsGaussRunner::Instance());
    }; //randomize_weights_gauss

}; //pann
