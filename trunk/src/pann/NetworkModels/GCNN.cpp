//GCNN.cpp

#include <boost/foreach.hpp>

#include "GCNN.h"
#include "Core/Weight.h"
#include "Core/Random.h"
#include "NeuronFactories/PyramidalNeuron.h"

using namespace std;

namespace pann
{
    plane_t
    make_plane(plane_data_t plane_data, bool conv_plane)
    {
        /*
        Convolutional layer

        x1,x2,x3,x4 - inputs
        y = f((x1+x2+x3+x4) * W + bias)
        f(x) = tanh(x)

        According to LeCunn each plane in CONV layer uses only 2
        trainable parameters - shared weight and shared bias
        */

        plane_t plane;

        plane.neurons = new boost::multi_array<NeuronPtr, 2>(boost::extents[plane_data.height][plane_data.width]);
        WeightPtr shared_bias(new Weight());

        for(int i = 0; i < plane_data.height; ++i)
            for(int j = 0; j < plane_data.width; ++j)
                (*plane.neurons)[i][j] = NeuronFactory::PyramidalNeuron(plane_data.tf, shared_bias);

        plane.weights = new boost::multi_array<WeightPtr, 2>(boost::extents[plane_data.window_height][plane_data.window_width]);
        WeightPtr shared_weight(new Weight());

        for(int i = 0; i < plane_data.window_height; ++i)
            for(int j = 0; j < plane_data.window_width; ++j)
                if(!conv_plane)
                    (*plane.weights)[i][j] = WeightPtr(new Weight());
                else
                    (*plane.weights)[i][j] = shared_weight;

        return plane;
    }; //make_plane

    void
    connect_planes(plane_t& prev_plane, plane_t& next_plane)
    {
        /*
         * Уместить `N` отрезков длинны `a` в одном отрезке длинны `A`,
         * обеспечив однородную плотность покрытия
         * Задача сводится к равномерному размещению N точек (центров масс отрезков a)
         * на отрезке (a/2; A - a/2) или на отрезке (0; A - a), если точки N - начала отрезков `a`
         * Отрезки размещаются с шагом (A - a) / (N - 1)
         */
        unsigned vert_step = 0;
        if(next_plane.neurons->size() > 1)
            vert_step = (prev_plane.neurons->size() - next_plane.weights->size()) / (next_plane.neurons->size() - 1);

        unsigned horiz_step = 0;
        if((*next_plane.neurons)[0].size() > 1)
            horiz_step = ((*prev_plane.neurons)[0].size() - (*next_plane.weights)[0].size()) / ((*next_plane.neurons)[0].size() - 1);

        Net fake_net;

        for(unsigned i = 0; i < next_plane.neurons->size(); ++i)
            for(unsigned j = 0; j < (*next_plane.neurons)[0].size(); ++j)
                for(unsigned m = 0; m < next_plane.weights->size(); ++m)
                    for(unsigned n = 0; n < (*next_plane.weights)[0].size(); ++n)
                        fake_net.add_connection(
                                (*prev_plane.neurons)[i * vert_step + m][j * horiz_step + n],
                                (*next_plane.neurons)[i][j],
                                (*next_plane.weights)[m][n]);

    }; //connect_planes

    NetPtr
    make_net(net_data_t& net_data)
    {
        for(unsigned i = 0; i < net_data.connection_matrix.size(); ++i)
           for(unsigned j = 0; j < net_data.connection_matrix[0].size(); ++j)
               if(net_data.connection_matrix[i][j])
                   connect_planes(net_data.planes[i], net_data.planes[j]);

        NetPtr net(new Net());
        for(unsigned i = 0; i < net_data.planes.at(0).neurons->size(); ++i)
            for(unsigned j = 0; j < (*net_data.planes[0].neurons)[0].size(); ++j)
                net->add_input_neuron((*net_data.planes[0].neurons)[i][j]);

        return net;
    }; //make_net

    NetPtr
    make_convnet(
            vector<unsigned> layers,
            Float connection_density,
            unsigned window_height,
            unsigned window_width,
            unsigned window_vert_overlap,
            unsigned window_horiz_overlap,
            TfPtr input_tf,
            TfPtr ss_tf,
            TfPtr conv_tf,
            TfPtr output_tf)
    {
        assert(0.0 < connection_density);
        assert(connection_density <= 1.0);
        assert(window_height > window_vert_overlap);
        assert(window_width > window_horiz_overlap);
        assert(layers.size() > 0);
        for(unsigned i = 0; i < layers.size(); ++i)
            assert(layers[i] > 0);

        /*
        Each layers[] contains information about planes count in corresponding
        level. Level consists of two layers: convolutional and subsampling
        Plus one input and one output layer
        */
        layers.insert(layers.begin(), 1); //For input layer

        unsigned conv_range = 2;

        typedef vector<plane_t> layer_t;
        typedef vector<layer_t> model_t;

        model_t model;

        //Output layer
        model.push_back(layer_t());
        plane_data_t output_plane_data;
        output_plane_data.height = 1;
        output_plane_data.width = 1;
        output_plane_data.window_height = window_height;
        output_plane_data.window_width = window_width;
        output_plane_data.tf = output_tf;
        for(unsigned plane_no = 0; plane_no < layers[layers.size() - 1]; ++plane_no)
            model[model.size() - 1].push_back(make_plane(output_plane_data));

        //ss-conv pairs
        for(signed current_layer_no = layers.size() - 2; current_layer_no >= 0; --current_layer_no)
        {
            //model[0] still holds next ss layer
            unsigned next_layer_ss_plane_height = model[0][0].neurons->size();
            unsigned next_layer_ss_plane_width = (*model[0][0].neurons)[0].size();
            unsigned current_layer_conv_plane_height = next_layer_ss_plane_height * (window_height - window_vert_overlap) + window_vert_overlap;
            unsigned current_layer_conv_plane_width = next_layer_ss_plane_width * (window_width - window_horiz_overlap) + window_horiz_overlap;

            bool is_input_layer = ( 0 == current_layer_no );

            model.insert(model.begin(), layer_t()); //conv
            plane_data_t conv_plane_data;
            conv_plane_data.height = current_layer_conv_plane_height;
            conv_plane_data.width = current_layer_conv_plane_width;
            conv_plane_data.window_height = conv_range;
            conv_plane_data.window_width = conv_range;
            conv_plane_data.tf = conv_tf;

            plane_data_t ss_plane_data;
            if(!is_input_layer) {
                model.insert(model.begin(), layer_t()); //ss
                ss_plane_data.height = conv_plane_data.height * conv_range;
                ss_plane_data.width = conv_plane_data.width * conv_range;
                ss_plane_data.window_height = window_height;
                ss_plane_data.window_width = window_width;
                ss_plane_data.tf = ss_tf;
            };

            for(unsigned plane_no = 0; plane_no < layers[current_layer_no]; ++plane_no)
            {
                if(!is_input_layer) {
                    model[0].push_back(make_plane(ss_plane_data));
                    model[1].push_back(make_plane(conv_plane_data, true));
                } else {
                    conv_plane_data.tf = input_tf;
                    model[0].push_back(make_plane(conv_plane_data, true));
                };
            };
        };

        //calculating connection matrix
        net_data_t net_data;
        unsigned flat_planes_count = 0;
        for(unsigned layer_no = 0; layer_no < model.size(); ++layer_no)
            for(unsigned plane_no = 0; plane_no < model[layer_no].size(); ++plane_no)
                flat_planes_count++;

        net_data.connection_matrix.resize(boost::extents[flat_planes_count][flat_planes_count]);
        for(unsigned i = 0; i < flat_planes_count; ++i)
            for(unsigned j = 0; j < flat_planes_count; ++j)
                net_data.connection_matrix[i][j] = false;

        net_data.planes.push_back(model[0][0]); //input plane

        for(unsigned layer_no = 1; layer_no < model.size(); ++layer_no)
        {
            bool is_conv_layer = ( 0 == layer_no % 2 );
            unsigned flat_prev_layer_planes_end = net_data.planes.size();
            unsigned flat_prev_layer_planes_begin = flat_prev_layer_planes_end - model[layer_no - 1].size();

            for(unsigned plane_no = 0; plane_no < model[layer_no].size(); ++plane_no)
            {
                net_data.planes.push_back(model[layer_no][plane_no]);

                unsigned flat_plane_no = flat_prev_layer_planes_end + plane_no;
                if(is_conv_layer) {
                    net_data.connection_matrix[flat_prev_layer_planes_begin + plane_no][flat_plane_no] = true;
                } else {
                    for(unsigned prev_layer_plane_no = flat_prev_layer_planes_begin; prev_layer_plane_no < flat_prev_layer_planes_end; ++prev_layer_plane_no)
                        net_data.connection_matrix[prev_layer_plane_no][flat_plane_no] = rand_coin(connection_density);
                    //FIXME: zero connections between two consequtive layer pairs
                }
            };
        };

        NetPtr net = make_net(net_data);

        /*
        //print model
        cout<<"Model\n";
        for(unsigned layer_no = 0; layer_no < model.size(); ++layer_no)
        {
            for(unsigned plane_no = 0; plane_no < model[layer_no].size(); ++plane_no)
                cout<<model[layer_no][plane_no].neurons->size()<<'x'<<(*model[layer_no][plane_no].neurons)[0].size()<<' ';
            cout<<'\n';
        };

        //print connection matrix
        cout<<"Connection matrix:\n";
        for(unsigned i = 0; i < net_data.connection_matrix.size(); ++i)
            for(unsigned j = 0; j < net_data.connection_matrix[0].size(); ++j)
                cout<<i<<" -> "<<j<<" = "<<net_data.connection_matrix[i][j]<<'\n';

        //adding trace information
        unsigned neuron_uid = 0;
        unsigned weight_uid = 0;
        for(unsigned layer_no = 0; layer_no < model.size(); ++layer_no)
            for(unsigned plane_no = 0; plane_no < model[layer_no].size(); ++plane_no)
                for(unsigned i = 0; i < model[layer_no][plane_no].neurons->size(); ++i)
                    for(unsigned j = 0; j < (*model[layer_no][plane_no].neurons)[0].size(); ++j) {
                        NeuronPtr n = (*model[layer_no][plane_no].neurons)[i][j];
                        n->set_attr(hash("layer"), layer_no);
                        n->set_attr(hash("plane"), plane_no);
                        n->set_attr(hash("y"), i);
                        n->set_attr(hash("x"), j);
                        n->set_attr(hash("uid"), neuron_uid++);
                        BOOST_FOREACH( const Link& link, n->input_links )
                            link.get_weight()->set_attr(hash("uid"), weight_uid++);
                    };
        */
        /*
        const NetCache & cache = net->get_cache();
        cout<<"Cache layers["<<cache.layers.size()<<"] : ";
        for(unsigned i = 0; i < cache.layers.size(); ++i)
            cout<<cache.layers[i].size()<<" ";
        cout<<endl;

        cout<<"Tracing:\n";
        for(unsigned layer_no = 0; layer_no < cache.layers.size(); ++layer_no)
        {
            cout<<"Layer "<<layer_no<<'\n';
            for(unsigned neuron_no = 0; neuron_no < cache.layers[layer_no].size(); ++neuron_no)
            {
                NeuronPtr n = cache.layers[layer_no][neuron_no];
                cout<<"uid:\t"<<n->get_attr(pann::hash("uid"))<<"\nlayer:\t"<<n->get_attr((pann::hash("layer")))<<
                        "\nplane:\t"<<n->get_attr(pann::hash("plane"))<<"\nx:\t"<<n->get_attr(pann::hash("x"))<<
                        "\ny:\t"<<n->get_attr(pann::hash("y"))<<"\n";
                BOOST_FOREACH( const Link & link, n->input_links )
                        cout<<"-> "<<link.get_to()->get_attr(pann::hash("uid"))<<", w = "<<link.get_weight()->get_attr(pann::hash("uid"))<<'\n';
                cout<<endl;
            };
        };
        */

        return net;

    }; //make_convnet

}; //pann

