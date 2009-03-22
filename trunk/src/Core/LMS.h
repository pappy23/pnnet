
#ifndef LMS_H
#define LMS_H

#include "Includes.h"
#include "Net.h"
#include "LearningAlgorithm.h"

namespace pann
{
    class LMS : public LearningAlgorithm
    {
        /* Public interface */
    public:
        /**
         * Adds LearningHint to network object,
         * sets different parametrs, such as learning rate,
         * momentum etc.
         */
        static void init(Net& _net /* Params */)
        {
            if(_net.learningHint)
                delete _net.learningHint;

            LearningHint::LmsNet* net_lh = new LearningHint::LmsNet();
            _net.learningHint = (LearningHint::Base*) net_lh;
            net_lh->learningRate = 0.03;
        };

        /**
         * Does one forward propagation and backpropagation,
         * while changing weights.
         * If _trainData.data.size() == 1, then does iterative learning,
         * else - batch learning.
         * All data is used for training and no testing performed
         */
        static void train(Net& _net, TrainData& _trainData)
        {
            LearningHint::LmsNet* net_lh = dynamic_cast<LearningHint::LmsNet*>(_net.learningHint);
            if(!_net.learningHint || !net_lh)
                throw Exception::ObjectNotFound()<<"LMS::train(): Net was not initialized for LMS training\n";
        };
    };
}; //pann

#endif //LMS_H

