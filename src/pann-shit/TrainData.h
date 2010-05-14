#ifndef TRAINDATA_H
#define TRAINDATA_H

#include <vector>

#include "pann.h"

namespace pann
{
    class TrainPattern
    {
        typedef std::valarray<Float> V;

    public:
        TrainPattern(unsigned int _input_size, unsigned int _output_size)
        {
            resize(_input_size, _output_size);
        };

        virtual ~TrainPattern() {};

        V& input()          { return m_input; };
        V& actual_output()  { return m_actual_output; };
        V& desired_output() { return m_desired_output; };
        const V& input() const          { return m_input; };
        const V& actual_output() const  { return m_actual_output; };
        const V& desired_output() const { return m_desired_output; };
        V error() const { return m_desired_output - m_actual_output; };

    private:
        std::valarray<Float> m_input;
        std::valarray<Float> m_actual_output;
        std::valarray<Float> m_desired_output;

        void resize(unsigned int _input_size, unsigned int _output_size)
        {
            m_input.resize(_input_size);
            m_actual_output.resize(_output_size);
            m_desired_output.resize(_output_size);
        }
    }; //TrainPattern

    typedef std::vector<TrainPattern> TrainData;

}; //pann

#endif

