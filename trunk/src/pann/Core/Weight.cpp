//Weight.cpp

#include "Weight.h"

namespace pann
{
        Float
        Weight::get_value() const
        {
            return m_value;
        }; //get_value

        void
        Weight::add_value(Float delta)
        {
            if(m_usage_count <= 2)
                m_value += delta;
            else
            {
                boost::mutex::scoped_lock(m_mutex);
                m_value += delta;
            }
        }; //add_value

        void
        Weight::set_value(Float value)
        {
            if(m_usage_count <= 2)
                m_value = value;
            else
            {
                boost::mutex::scoped_lock(m_mutex);
                m_value = value;
            }
        }; //set_value

        unsigned
        Weight::get_usage_count() const
        {
            return m_usage_count;
        }; //get_usage_count

        void
        Weight::inc_usage_count(unsigned delta = 1)
        {
            m_usage_count += delta;
        }; //inc_usage_count

        void
        Weight::dec_usage_count(unsigned delta = 1)
        {
            m_usage_count -= delta;
        }; //dec_usage_count
}; //pann
