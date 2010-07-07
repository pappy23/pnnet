#ifndef PANN_NETWORKMODELS_GCNN_DEFINED
#define PANN_NETWORKMODELS_GCNN_DEFINED

#include <boost/multi_array.hpp>

#include "Includes/Std.h"
#include "Core/Net.h"
#include "TF/Linear.h"
#include "TF/TanH.h"

namespace pann
{
    typedef struct {
        int width;
        int height;
        int window_width;
        int window_height;
        TfPtr tf;
    } plane_data_t;

    typedef struct {
        boost::multi_array<NeuronPtr, 2> * neurons;
        boost::multi_array<WeightPtr, 2> * weights;
    } plane_t;

    typedef struct {
        std::vector<plane_t> planes;
        boost::multi_array<bool, 2> connection_matrix; //[from][to]
        //TODO: replace bool with Float and give it connection density meaning
    } net_data_t;

    plane_t make_plane(plane_data_t plane_data, bool conv_plane = false);
    NetPtr make_net(net_data_t& net_data);

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

