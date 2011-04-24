//Random.cpp

#include <ctime>

#include "Random.h"

namespace pann
{
    boost::lagged_fibonacci44497 float_random_generator;
    boost::mt19937 int_random_generator;

    void
    seed(unsigned value)
    {
        if(0 == value) {
            float_random_generator.seed(time(0));
            int_random_generator.seed(time(0));
        } else {
            float_random_generator.seed(value);
            int_random_generator.seed(value);
        }
    }; //seed

    Float
    rand01()
    {
        /*
        static boost::uniform_real<Float> distribution(0, 1);
        static boost::variate_generator<
            boost::lagged_fibonacci44497,
            boost::uniform_real<Float>
        > generator(float_random_generator, distribution);

        return generator();
        */
        //return 0.5; // chosen by fair dice roll
        return Float(std::rand())/RAND_MAX;
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
        boost::uniform_int<> dist(a, b);
        boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(int_random_generator, dist);

        return die();
    }; //rand_int
}; //pann

