//GCNN.cpp

#include "GCNN.h"
#include "Core/Tf.h"
#include "Includes/Std.h"

using namespace std;

namespace pann
{
    void ass(bool cond)
    {
        if(!cond)
            throw Exception()<<"assert";
    };

    typedef struct {
        int width;
        int height;
        int window_width;
        int window_height;
        TfPtr tf;
    } plane_data_t;

    typedef struct {
        plane_data_t ss_plane_data;
        plane_data_t conv_plane_data;
    } col_data_t;

    typedef struct {
        vector<col_data_t> col_data;
    } layer_data_t;

    typedef struct {
        vector<layer_data_t> layer_data;
    } net_data_t;

    typedef vector<NeuronPtr>       row_t;
    typedef vector<row_t>           plane_t;
    typedef pair<plane_t, plane_t>  col_t;
    typedef vector<col_t>           layer_t;

    plane_t make_plane(plane_data_t plane_data)
    {
        plane_t plane;

        for(int i = 0; i < plane_data.height; ++i)
        {
            row_t row;
            for(j = 0; j < plane_data.width; ++j)
            {
                row.push_back(NeuronFactory::PyramidalNeuron(plane_data.tf));
            };
            plane.push_back();
        };

        return plane;
    }; //make_plane

    void connect_planes(const plane_t& prev_plane, const plane_t& next_plane, plane_data_t next_plane_data)
    {
        /**
         * Уместить `N` отрезков длинны `a` в одном отрезке длинны `A`,
         * обеспечив однородную плотность покрытия
         * Дано:
         * А
         * а
         * N
         *
         * Задача сводится к равномерному размещению N точек (центров масс отрезков a)
         * на отрезке (a/2; A - a/2) или на отрезке (0; A - a), если точки N - начала отрезков `a`
         * Отрезки размещаются с шагом (A - a) / (N - 1)
         */

        vector<vector<WeightPtr> > shared_weights;
        for(int i = 0; i < next_plane_data.window_height; ++i)
        {
            vector<WeightPtr> row;
            for(int j = 0; j < next_plane_data.window_width; ++j)
                row.push_back(new Weight());
            shared_weights.push_back(row);
        };

        int vert_step = prev_plane.size();
        int horiz_step = prev_plane[0].size();

        Net fake_net;
        for(int i = 0; i < next_plane_data.height; ++i)
            for(int j = 0; j < next_plane_data.width; ++j)
                for(int m = 0; m < next_plane_data.window_height; ++m)
                    for(int n = 0; n < next_plane_data.window_width; ++n)
                        fake_net.add_connection(
                                prev_plane[i * vert_step + m][j * horiz_step + n],
                                next_plane[i][j],
                                shared_weights[i][j]
                                );

    }; //connect_planes

    col_t make_col(col_data_t col_data)
    {
        plane_t ss_plane = make_plane(col_data.ss_plane_data);
        plane_t conv_plane = make_plane(col_data.conv_plane_data);

        connect_planes(ss_plane, conv_plane, col_data.conv_plane_data);

        return std::make_pair(ss_plane, conv_plane);
    }; //make_col

    NetPtr
    gcnn(const net_data_t& net_data)
    {
        NetPtr net(new Net());

        ass(net_data.layers_data.size() > 2);

        for(int layer_no = 1; i < net_data.layers_data.size() - 1; ++layer_no)
        {
        }

        return net;
    }; //gcnn

}; //pann

