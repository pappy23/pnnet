#ifndef PANN_NETWORKMODELS_GCNN_DEFINED
#define PANN_NETWORKMODELS_GCNN_DEFINED

#include "Includes/Std.h"
#include "Core/Net.h"
#include "TF/Linear.h"
#include "TF/TanH.h"

namespace pann
{
    NetPtr make_convnet(
            std::vector<unsigned> layers,
            Float connection_density = 1.0,
            unsigned window_height = 5,
            unsigned window_width = 5,
            unsigned window_vert_overlap = 3,
            unsigned window_horiz_overlap = 3,
            TfPtr input_tf = Linear::Instance(),
            TfPtr ss_tf = TanH::Instance(),
            TfPtr conv_tf = TanH::Instance(),
            TfPtr output_tf = TanH::Instance()
    );
}; //pann

#endif //PANN_NETWORKMODELS_GCNN_DEFINED

