#ifndef UTIL_H
#define UTIL_H

#include "pann-shit.h"
#include "config.h"

void random_seed(unsigned seed);
std::string cur_time();
TrainPattern imgm2tp(const FaceT& data, unsigned men);

#endif //UTIL_H

