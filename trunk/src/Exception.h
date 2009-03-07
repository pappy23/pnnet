//Exception.h                                                                                                                    
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Includes.h"

namespace pann
{
    namespace Exception
    {
        class Base
        {
        protected:
            std::ostringstream textStream;

        public:
            Base() { };
            Base(Base& _rvalue) : textStream(_rvalue.textStream.str()) { };

            virtual ~Base() { };

            std::string text()
            {
                return textStream.str();
            };

            template<typename T> Base& operator<<(const T& value)
            {
                textStream << value;

                return *this;
            }
        };

        class ObjectNotFound : public Base { };
        class ElementExists  : public Base { };
    }; //Exception

}; //namespace NNet

#endif
