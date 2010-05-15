//RandomizeWeightsAccordingToInputsCount.cpp

#include <boost/foreach.hpp>

#include "RandomizeWeightsAccordingToInputsCount.h"

REGISTER_SINGLETON_CPP(RandomizeWeightsAccordingToInputsCountRunner);

#include "Core/Random.h"

namespace pann {
    void
    RandomizeWeightsAccordingToInputsCountRunner::run(Object const * net, NeuronPtr neuron) const
    {
        Float min = net->get_attr(hash("RW_MIN"));
        Float max = net->get_attr(hash("RW_MAX"));

        Float C = sqrt(Float(neuron->input_links.size()));
        if(C == 0)
            C = 10.0;

        //Tune bias values
        if(neuron->bias)
            neuron->bias->add_value(pann::rand(min, max) / C - neuron->bias->get_value());

        //Link weights
        BOOST_FOREACH(const Link& link, neuron->input_links)
            link.get_weight()->add_value(pann::rand(min, max) / C - link.get_weight()->get_value());
    }; //run

    void
    randomize_weights_according_to_inputs_count(NetPtr net, Float min, Float max)
    {
        net->set_attr(hash("RW_MIN"), min);
        net->set_attr(hash("RW_MAX"), max);
        net->run(RandomizeWeightsAccordingToInputsCountRunner::Instance(), Net::ForwardRun);
    }; //randomize_weights_according_to_inputs_count

}; //pann
