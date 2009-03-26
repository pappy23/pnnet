//Exception.cpp

#include "Exception.h"

namespace pann
{
    namespace Exception
    {
        Base::Base()
        {
        } //Base

        Base(Base& _rvalue) 
        {
            textStream = _rvalue.textStream.str();
        } //Base

        Base::~Base()
        {
        } //~Base

        const char*
        Base::what() const
        {
            return textStream.str().c_str();
        } //what

    }; //Exception
}; //pann

#endif
