#ifndef CONVOLUTIONALNETWORK_H
#define CONVOLUTIONALNETWORK_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"

#include "Core/Tf.h"
#include "TF/TanH.h"
#include "TF/Linear.h"

using std::vector;

namespace pann
{
    /**
     * Typedefs for Convolutional network architecture
     */
    namespace ConvolutionalNetworkTypes
    {
        typedef vector<NeuronPtr> Row;
        typedef vector<Row> Plane;
        typedef vector<Plane> Layer;
        typedef vector<Layer> Model;
    }

    /**
     * This functions constructs Convolutional Network
     * @arg layers - number of planes in each Convolutional-Subsampling layer pair
     * @arg connection_density - used to generate random connection matrix between
     * consecutive layers
     * @arg window_width, @arg window_height - sliding window size
     * @arg window_horiz_overlap, @arg window_vert_overlap - windows overlap area
     * @arg input_af  - activation function for neurons in input layer
     * @arg conv_af   - activation function for neurons in convolutional sublayers
     * @arg ss_af     - activation function for neurons in subsampling sublayers
     * @arg output_af - activation function for neurons in output layer
     *
     * Detailed description of convolutional neural network model you can find in
     * [Yann LeCun, Gradient-based learning applied to document recognition, 1998]
     * and in other LeCun articles
     * For realization details @see ConvolutionalNetworkModel()
     */
    NetPtr
    ConvolutionalNetwork(
        vector<unsigned> layers,
        Float connection_density = 0.5,
        unsigned window_width  = 5,
        unsigned window_height = 5,
        unsigned window_horiz_overlap = 3,
        unsigned window_vert_overlap  = 3,
        TfPtr input_af = TanH::Instance(),
        TfPtr conv_af  = TanH::Instance(),
        TfPtr ss_af    = TanH::Instance(),
        TfPtr output_af= TanH::Instance()
        );

    /**
     * This function actually constructs convolutional network and returns
     * Model. This Model usually used to build Net object from it
     * ConvolutionalNetworkModel should not be used by pann user directly
     * For parameters description @see ConvolutionalNetwork()
     */
    ConvolutionalNetworkTypes::Model
    ConvolutionalNetworkModel(
        vector<unsigned> layers,
        Float connection_density = 0.5,
        unsigned window_width  = 5,
        unsigned window_height = 5,
        unsigned window_horiz_overlap = 3,
        unsigned window_vert_overlap  = 3,
        TfPtr input_af = TanH::Instance(),
        TfPtr conv_af  = TanH::Instance(),
        TfPtr ss_af    = TanH::Instance(),
        TfPtr output_af= Linear::Instance()
        );

}; //pann

#endif

