//TrainDataGenerator.cpp

#include <fstream>

#include <boost/foreach.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
//#include <boost/gil/extension/numeric/sampler.hpp>
//#include <boost/gil/extension/numeric/resample.hpp>

#include "Core/Util.h"
#include "Core/Net.h"
#include "Core/Runner.h"

#include "TrainDataGenerator.h"

#include "TrainData.h"
#include "TrainPattern.h"

using namespace std;
using namespace boost;
using namespace boost::gil;

namespace pann
{
    namespace Util
    {
        Float
        test(Net& _net, TrainData& _td)
        {
            BOOST_FOREACH(TrainPattern& tp, _td.data)
            {
                _net.setInput(tp.input);
                _net.run(FeedforwardPropagationRunner::Instance());
                _net.getOutput(tp.error); //actual output
                tp.error = tp.desired_output - tp.error; 
            }

            return _td.getMse();
        } //test

    }; //Util

    namespace DataGenerator
    {
        TrainData
        divide(TrainData& _td, unsigned _percentage)
        {
            TrainData new_td;
            unsigned count = _td.data.size() * _percentage / 100.0;
            for(unsigned i = 0; i < count; i++)
            {
                new_td.data.push_back(_td.data.back());
                _td.data.pop_back();
            }

            return new_td;
        } //divide

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

        valarray<Float>
        jpeg_gray2valarray(string _filename, unsigned _width, unsigned _height)
        {
            gray8_image_t img;
            jpeg_read_image(_filename, img);

            if(_width == 0 and _height == 0)
            {
                _width = view(img).width();
                _height = view(img).height();
            }

            valarray<Float> result(_width * _height);
            
            //TODO: fix resampling
            //Scale the image to (_width)x(_height) pixels using bilinear resampling
            //rgb8_image_t scaled_img(_width, _height);
            //resize_view(const_view(img), view(scaled_img), bilinear_sampler());
            //rgb8_view_t v = view(scaled_img);
            gray8_view_t v = view(img);

            unsigned i = 0;
            gray8_view_t::iterator iter = v.begin();
            for(; iter != v.end() and i < _width * _height; ++iter)
                result[i++] = at_c<0>(*iter);

            return result;
        } //jpeg2valarray

        valarray<Float>
        ppm2valarray(string _filename, unsigned _width, unsigned _height)
        {
            //TODO use boost::iostreams, particulary shell_comments_filter
            valarray<Float> result;

            std::cout<<"PPM test\n";
            std::ifstream file(_filename.c_str(), ios_base::in | ios_base::binary);


            return result;
        } //ppm2valarray

        valarray<Float>
        pgm2valarray(string _filename, unsigned _width, unsigned _height)
        {
            valarray<Float> result;

            return result;
        } //pgm2valarray

    }; //DataGenerator
}; //pann

