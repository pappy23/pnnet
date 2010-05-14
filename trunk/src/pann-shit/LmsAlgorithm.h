
#ifndef LMSALGORITHM_H
#define LMSALGORITHM_H

#include "pann.h"

namespace pann
{
    class Lms
    {
        /* Public interface */
    public:
        /**
         * Does one forward propagation and backpropagation,
         * while changing weights.
         * If _trainData.data.size() == 1, then does iterative learning,
         * else - batch learning.
         * All data is used for training and no testing performed
         */
        template<class T>
        static void train(NetPtr _net, T& _trainData)
        {
            const vector<NeuronPtr>& output_neurons = *(_net->get_cache().layers.end() - 2);

            typename T::iterator iter = _trainData.begin();
            for(; iter != _trainData.end(); ++iter)
            {
                _net->set_input(iter->input());
                _net->run(FeedforwardPropagationRunner::Instance());
                _net->get_output(iter->actual_output());
                valarray<Float> error = iter->error();

                //Put error information to output neurons
                for(unsigned i = 0; i < output_neurons.size(); ++i)
                    output_neurons[i]->set_attr(hash("lms_error"), error[i]);

                _net->run(LmsBackpropagationRunner::Instance());
            }

            _net->get_attr_ref(hash("lms_epoch")) += 1;
        }
    }; //Lms
}; //pann

#endif //LMS_H

