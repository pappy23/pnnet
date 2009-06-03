#include "Image.h"

using namespace std;

namespace pann
{
    Image::Image(const unsigned _width, const unsigned _height, const valarray<Float>& _data) 
        : m_width(_width), m_height(_height)
    {
        if( _data.size() % (_width * _height) != 0 )
            throw SizeMismatch()<<"Can't determine layers count from dimensions given\n";

        const unsigned layers_count = _data.size() / (_width * _height);
        m_bmap.resize(layers_count);

        for(unsigned layer = 0; layer < layers_count; ++layer)
            m_bmap[layer].resize(_width * _height);

        for(unsigned i = 0; i < _width * _height; ++i)
            for(unsigned layer = 0; layer < layers_count; ++layer)
            {
                Float pixel = _data[i * layers_count + layer];
                if(pixel < 0.0 || pixel > 255.0)
                {
                    m_bmap.clear();
                    throw SizeMismatch()<<"_data[] out of range [0; 255]\n";
                }

                m_bmap[layer][i] = (unsigned char) pixel;
            }
    } //Image

    Image::~Image()
    {
    } //~Image

    valarray<Float>
    Image::getAverageValarray() const
    {
        const unsigned layers_count = m_bmap.size();

        valarray<Float> result(m_width * m_height);

        for(unsigned i = 0; i < m_width * m_height; ++i)
        {
            Float pixel = 0.0;
            for(unsigned j = 0; j < layers_count; ++j)
                pixel += m_bmap[j][i];

            result[i] = pixel / Float(layers_count);
        }

        return result;
    } //getAverageValarray

    valarray<Float>
    Image::getCompositeValarray() const
    {
        const unsigned layers_count = m_bmap.size();

        valarray<Float> result(m_width * m_height * layers_count);

        for(unsigned i = 0; i < m_width * m_height; ++i)
            for (unsigned layer = 0; layer < layers_count; ++layer)
                result[i * layers_count + layer] = m_bmap[layer][i];

        return result;
    } //getCompositeValarray

}; //pann

