//Random.cpp

#include <boost/random.hpp>

#include "Random.h"

namespace pann
{
    Float
    rand01()
    {
        static boost::lagged_fibonacci44497 engine;
        static boost::uniform_real<Float> distribution(0, 1);
        static boost::variate_generator<
            boost::lagged_fibonacci44497,
            boost::uniform_real<Float>
        > generator(engine, distribution);

        return generator();
    }; //rand01

    Float
    rand(Float min, Float max)
    {
        //Generate v from (0; 1) and scale it to (_min; _max) range
        Float v = rand01();
        Float a = ( max - min );
        Float b = max - a;
        v = a * v + b;

        return v;
    }; //rand

    bool
    rand_coin(Float probability)
    {
        return rand01() < probability;
    }; //rand_coin

    int
    rand_int(int a, int b)
    {
        static boost::mt19937 gen;
        boost::uniform_int<> dist(a, b);
        boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);

        return die();
    }; //rand_int
}; //pann

