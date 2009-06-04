#ifndef IMAGE_H
#define IMAGE_H

#include "Includes/Std.h"
#include "Core/Type.h"
#include "Core/Exception.h"

using std::valarray;
using std::vector;

namespace pann
{
    /**
     * Image is stored in vector<Layer>. Layer = vector<char>. Each point
     * is represented as 0-255 value
     */
    class Image
    {
    public:
        /**
         * Constructs empty image without layers
         */
        Image();

        /**
         * Construct Image from valarray
         * Layers number is determined automatically
         * May raise exception if _data doesn't match declared dimensions
         * @param _width
         * @param _height - layer dimensions
         * @param _data - data:
         *
         * Picture:
         *  ___
         * |_|_|
         * |_|_|  <-- row (R2), each cell consists from 3 layers(L1-L3)
         *
         * _data:
         * [R1C1L1, R1C1L2, R1C1L3, R1C2L1, R1C2L2, ..., R2C2L2, R2C2L3]
         */
        Image(const unsigned _width, const unsigned _height, const valarray<unsigned char>& _data);
        Image(const unsigned _width, const unsigned _height, const valarray<Float>& _data);
        ~Image();

        /**
         * @return valarray of average values among all layers
         * [R1C1LX, R1C2LX, R2C1LX, R2C2LX], LX = (L1+L2+L3) / 3
         * @see Image()
         */
        valarray<Float> getAverageValarray() const;

        /**
         * @return valarray of all layers. Pixel values are pushed to
         * result valarray in round robin fashion (@see Image())
         */
        valarray<Float> getCompositeValarray() const;

    private:
        void createImageFromCharValarray(const valarray<unsigned char>& _data);

        unsigned m_width;
        unsigned m_height;
        vector<vector<unsigned char> > m_bmap;
    };

}; //pann

#endif

