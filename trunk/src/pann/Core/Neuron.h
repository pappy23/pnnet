#ifndef PANN_CORE_NEURON_H_INCLUDED
#define PANN_CORE_NEURON_H_INCLUDED

#include <boost/bind.hpp>
#include "Includes/Std.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Link.h"
#include "Tf.h"
#include "Runner.h"

namespace pann
{
    class Neuron : public Object
    {
    public:
        Neuron(TfPtr tf, WeightPtr bias, RunnerPtr fire, RunnerPtr learn)
            : tf(tf), bias(bias), fire(fire), learn(learn)
        {
        };
        virtual ~Neuron() {};

        Float input;
        Float output;

        std::vector<Link> input_links;
        std::vector<Link> output_links;

        TfPtr tf;
        WeightPtr bias;
        RunnerPtr fire;
        RunnerPtr learn;

    private:
        friend class Net;

        typedef struct {
            static bool comp(NeuronPtr to, const Link& l) {
                return l.get_to() == to;
            }
        } ComparatorT;

        void add_in_connection(NeuronPtr to, WeightPtr weight)
        {
            input_links.push_back( Link(to, weight) );
        };

        void add_out_connection(NeuronPtr to, WeightPtr weight)
        {
            output_links.push_back( Link(to, weight) );
        };

        void remove_in_connection(NeuronPtr to)
        {
            remove_if(input_links.begin(), input_links.end(), bind(ComparatorT::comp, to, _1));
        };

        void remove_out_connection(NeuronPtr _to)
        {
            remove_if(output_links.begin(), output_links.end(), bind(ComparatorT::comp, _to, _1));
        };

    private:
        //friend template<class Archive> void Net::serialize(Archive & ar, const unsigned int version);
        Neuron() {};

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 //@see Net::serialize()
                 //& BOOST_SERIALIZATION_NVP(links_out)
                 //& BOOST_SERIALIZATION_NVP(links_in)
                 & BOOST_SERIALIZATION_NVP(input)
                 & BOOST_SERIALIZATION_NVP(output)
                 & BOOST_SERIALIZATION_NVP(bias)
                 & BOOST_SERIALIZATION_NVP(tf)
                 & BOOST_SERIALIZATION_NVP(fire)
                 & BOOST_SERIALIZATION_NVP(learn);
            };
    }; //Neuron
    ADD_PTR_TYPEDEF(Neuron);

}; //pann

#endif //PANN_CORE_NEURON_H_INCLUDED

