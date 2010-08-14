//util.cpp

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "util.h"

using namespace std;

void random_seed(unsigned seed)
{
    if(0 != seed) {
        srand(seed);
    }
    pann::seed(seed);
}; //random_seed

string cur_time()
{
    string result;
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    result += asctime (timeinfo);

    return result;
}; //cur_time

/**
 * Converts orl image to TrainPattern
 * @param _men - number of outputs
 */
TrainPattern imgm2tp(const FaceT& data, unsigned men)
{
    //Convert image to TrainPattern
    TrainPattern tp(92*92, men);
    tp.input() = data.img->getAverageValarray();
    squash(tp.input(), 0.0, 255.0, -1.8, +1.8);
    for(unsigned j = 0; j < men; ++j)
        tp.desired_output()[j] = -1.8;
    tp.desired_output()[data.man - 1] = +1.8;

    return tp;
}; //imgm2tp

