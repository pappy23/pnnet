#include "Image.h"

using namespace std;

namespace pann
{
    Image::Image(const unsigned _width, const unsigned _height, const valarray<unsigned char>& _data) 
        : m_width(_width), m_height(_height)
    {
        createImageFromCharValarray(_data);
    } //Image

    Image::Image(const unsigned _width, const unsigned _height, const valarray<Float>& _data) 
        : m_width(_width), m_height(_height)
    {
        if(_data.min() < 0.0 || _data.max() > 255.0)
            throw SizeMismatch()<<"_data[] out of range [0; 255]\n";

        valarray<unsigned char> us_data(_data.size());
        for(unsigned i = 0; i < _data.size(); ++i)
            us_data[i] = (unsigned char) _data[i];

        createImageFromCharValarray(us_data);
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

    void
    Image::createImageFromCharValarray(const valarray<unsigned char>& _data)
    {
        if( _data.size() % (m_width * m_height) != 0 )
            throw SizeMismatch()<<"Can't determine layers count from dimensions given\n";

        const unsigned layers_count = _data.size() / (m_width * m_height);
        m_bmap.resize(layers_count);

        for(unsigned layer = 0; layer < layers_count; ++layer)
            m_bmap[layer].resize(m_width * m_height);

        for(unsigned i = 0; i < m_width * m_height; ++i)
            for(unsigned layer = 0; layer < layers_count; ++layer)
                m_bmap[layer][i] = _data[i * layers_count + layer];
    } //createImageFromCharValarray

}; //pann

