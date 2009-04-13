//TrainDataGenerator.cpp

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
//#include <boost/gil/extension/numeric/sampler.hpp>
//#include <boost/gil/extension/numeric/resample.hpp>

#include "Core/Util.h"

#include "TrainDataGenerator.h"

#include "TrainData.h"
#include "TrainPattern.h"

using namespace std;
using namespace boost;
using namespace boost::gil;

namespace pann
{
    namespace DataGenerator
    {
        TrainData*
        generateFromFunction(Float _min, Float _max, unsigned _count, boost::function<Float (Float _x)> _f)
        {
            TrainData* td = new TrainData();

            for(unsigned i = 0; i < _count; ++i)
            {
                TrainPattern tp(1, 1);
                tp.input[0] = Util::rand(_min, _max);
                tp.desired_output[0] = _f(tp.input[0]);
                td->data.push_back(tp);
            }

            return td;
        } //generateFromFunction

        valarray<Float>
        jpeg_rgb2valarray(string _filename, unsigned _width, unsigned _height)
        {
            rgb8_image_t img;
            jpeg_read_image(_filename, img);

            if(_width == 0 and _height == 0)
            {
                _width = view(img).width();
                _height = view(img).height();
            }
            
            //TODO: fix resampling
            //Scale the image to (_width)x(_height) pixels using bilinear resampling
            //rgb8_image_t scaled_img(_width, _height);
            //resize_view(const_view(img), view(scaled_img), bilinear_sampler());
            //rgb8_view_t v = view(scaled_img);
            rgb8_view_t v = view(img);

            valarray<Float> result(_width * _height * 3);

            unsigned i = 0;
            rgb8_view_t::iterator iter = v.begin();
            for(; iter != v.end() and i < _width * _height * 3; ++iter)
            {
                result[i+0] = at_c<0>(*iter); //r
                result[i+1] = at_c<1>(*iter); //g
                result[i+2] = at_c<2>(*iter); //b
                i += 3;
            }

            return result;
        } //jpeg2valarray

    }; //DataGenerator
}; //pann

