
#ifndef TRAINDATAGENERATOR_H
#define TRAINDATAGENERATOR_H

#include "Core/Includes.h"
#include "Core/Type.h"
#include "Core/Util.h"
#include "TrainData.h"

namespace pann
{
    namespace DataGenerator
    {
        TrainData* generateFromFunction(Float _min, Float _max, unsigned _count, boost::function<Float (Float _x)> _f);

        /**
         * Read JPEG-file in RGB8 from disk and put it to valarray
         * pixel by pixel moving from left to right. Each pixel occupies 3 cells, because of RGB
         * Picture is scaled to (_width)x(_height), but if _width == _height == 0 then original size is kept
         */
        std::valarray<Float> jpeg_rgb2valarray(std::string _filename, unsigned _width = 0, unsigned _height = 0);

    }; //DataGenerator
}; //pann

#endif

