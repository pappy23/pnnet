//Tracer.cpp

#include <boost/foreach.hpp>
#include <iostream>

#include "Tracer.h"

REGISTER_SINGLETON_CPP(TracerRunner);

#include "Core/Neuron.h"
#include "Core/Random.h"

namespace pann {
    void
    TracerRunner::run(Object const * net, NeuronPtr neuron) const
    {
        /* It's broken
        neuron->set_attr(hash("trace_id"), rand_int(1, 1000000));
        std::cout<<neuron->get_attr(hash("trace_id"))<<" <- ("<<neuron->input_links.size()<<")\n";

        BOOST_FOREACH( const Link& link, neuron->input_links )
            std::cout<<link.get_to()->get_attr(hash("trace_id"));

        std::cout<<'\n'<<std::endl;
        */
    }; //run

    void
    trace(NetPtr net)
    {
        unsigned work_threads_count = net->get_work_threads_count();
        net->set_work_threads_count(1);

        std::cout<<"Trace:\n";
        net->run(TracerRunner::Instance());
        std::cout<<std::endl;

        net->set_work_threads_count(work_threads_count);
    }; //trace

}; //pann

