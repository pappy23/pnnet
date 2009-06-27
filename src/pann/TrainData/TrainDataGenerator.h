
#ifndef TRAINDATAGENERATOR_H
#define TRAINDATAGENERATOR_H

#include <boost/function.hpp>

#include <string>
#include <valarray>

#include "Core/Type.h"
#include "Squash.h"

namespace pann
{
    class TrainData;

    namespace Util
    {
        /**
         * Run network with _td and return mean squared error
         */
        Float test(Net& _net, TrainData& _td);

    }; //Util

    namespace DataGenerator
    {
        /**
         * Cut _percentage of TrainPatterns from _td.data and spawn new TrainData from them
         */
        TrainData divide2(TrainData& _td, unsigned _percentage);

        template<class T>
        std::pair<T, T>
        divide(T& _td, unsigned _percentage)
        {
            std::pair<T, T> result = make_pair(_td, T());
            unsigned count = unsigned(_td.size() * _percentage / 100.0);
            for(unsigned i = 0; i < count; i++)
            {
                result.second.push_back(result.first.back());
                result.first.pop_back();
            }

            return result;
        } //divide

        TrainData* generateFromFunction(Float _min, Float _max, unsigned _count, boost::function<Float (Float _x)> _f);

        /**
         * Read JPEG-file in RGB8 from disk and put it to valarray
         * pixel by pixel moving from left to right. Each pixel occupies 3 cells, because of RGB
         * Picture is scaled to (_width)x(_height), but if _width == _height == 0 then original size is kept
         */
        //std::valarray<Float> jpeg_rgb2valarray(std::string _filename, unsigned _width = 0, unsigned _height = 0);

        /**
         * Same as above, but for grayscale images
         */
        //std::valarray<Float> jpeg_gray2valarray(std::string _filename, unsigned _width = 0, unsigned _height = 0);

        /**
         * Read PPM file and put it to valarray
         */
        //std::valarray<Float> ppm2valarray(std::string _filename, unsigned _width = 0, unsigned _height = 0);

        /**
         * Read PGM file and put it to valarray
         */
        //std::valarray<Float> pgm2valarray(std::string _filename, unsigned _width = 0, unsigned _height = 0);

        /**
         * Read file _filename and construct TrainData from it
         * File format:
         * <total_classes>
         * </full/path/to/jpeg/image> <class>
         * Example:
         * /home/booble/faces/1.jpg 1
         */
        //TrainData* generateFromImageList(std::string _filename);

    }; //DataGenerator
}; //pann

#endif

