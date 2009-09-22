#ifndef CONVOLUTIONALNETWORK_H
#define CONVOLUTIONALNETWORK_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Core/ActivationFunction.h"

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
     * @arg _layers - number of planes in each Convolutional-Subsampling layer pair
     * @arg _connection_density - used to generate random connection matrix between
     * consecutive layers
     * @arg _window_width, @arg _window_height - sliding window size
     * @arg _window_horiz_overlap, @arg _window_vert_overlap - windows overlap area
     * @arg _input_af  - activation function for neurons in input layer
     * @arg _conv_af   - activation function for neurons in convolutional sublayers
     * @arg _ss_af     - activation function for neurons in subsampling sublayers
     * @arg _output_af - activation function for neurons in output layer
     *
     * Detailed description of convolutional neural network model you can find in
     * [Yann LeCun, Gradient-based learning applied to document recognition, 1998]
     * and in other LeCun articles
     * For realization details @see ConvolutionalNetworkModel()
     */
    NetPtr
    ConvolutionalNetwork(vector<unsigned> _layers,
        Float _connection_density = 0.5,
        unsigned _window_width  = 5,
        unsigned _window_height = 5,
        unsigned _window_horiz_overlap = 3,
        unsigned _window_vert_overlap  = 3,
        ActivationFunction::Base* _input_af = ActivationFunction::TanH::Instance(),
        ActivationFunction::Base* _conv_af  = ActivationFunction::TanH::Instance(),
        ActivationFunction::Base* _ss_af    = ActivationFunction::TanH::Instance(),
        ActivationFunction::Base* _output_af= ActivationFunction::Linear::Instance()
        );

    /**
     * This function actually constructs convolutional network and returns
     * Model. This Model usually used to build Net object from it
     * ConvolutionalNetworkModel should not be used by pann user directly
     * For parameters description @see ConvolutionalNetwork()
     */
    ConvolutionalNetworkTypes::Model
    ConvolutionalNetworkModel(vector<unsigned> _layers,
        Float _connection_density = 0.5,
        unsigned _window_width  = 5,
        unsigned _window_height = 5,
        unsigned _window_horiz_overlap = 3,
        unsigned _window_vert_overlap  = 3,
        ActivationFunction::Base* _input_af = ActivationFunction::TanH::Instance(),
        ActivationFunction::Base* _conv_af  = ActivationFunction::TanH::Instance(),
        ActivationFunction::Base* _ss_af    = ActivationFunction::TanH::Instance(),
        ActivationFunction::Base* _output_af= ActivationFunction::Linear::Instance()
        );

}; //pann

#endif

