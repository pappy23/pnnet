#ifndef UTIL_H
#define UTIL_H

#include "pann-shit.h"
#include "config.h"

void random_seed(unsigned seed);
std::string cur_time();
TrainPattern  imgm2tp(const FaceT& data, unsigned men);

void dispose_net(NetPtr pnet);
unsigned get_output_number(NetPtr pnet);
bool check_dataset(NetPtr pnet, DatasetT & dataset, map<unsigned, FaceT> & faces);

#endif //UTIL_H

