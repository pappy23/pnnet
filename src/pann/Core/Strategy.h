
#ifndef STRATEGY_H
#define STRATEGY_H

#include "Type.h"

namespace pann
{
    class Strategy
    {
    public:
        virtual void visit(NeuronPtr _n) = 0;

    }; //Strategy

    class PyramidalNeuronFireStrategy : public Strategy
    {
        //Singleton
        PyramidalNeuronFireStrategy() {};

    public:
        static StrategyPtr Instance()
        {
            static PyramidalNeuronFireStrategy self;
            return StrategyPtr(&self);
        };

        virtual void visit(NeuronPtr _n)
        {
        };

    }; //PyramidalNeuronFireStrategy

}; //pann

#endif

