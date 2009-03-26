/**
 * @file
 * Defines and implements all exception related stuff
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Includes.h"

namespace pann
{
    /**
     * Use case: throw Exception::CoolException()<<"This is exception; i = "<<5<<std::endl;
     * Don't forget to declare your CoolException, derived from Exception::Base
     */
    namespace Exception
    {
        //! Basic class for every exception
        class Base : public std::exception
        {
        public:
            virtual ~Base() throw();

            template<typename T> Base& operator<<(const T& value) throw()
            {
                textStream << value;

                return *this;
            };

            virtual const char* what() const throw();

        protected:
            Base() throw();
            Base(Base& _rvalue) throw();

        protected:
            std::ostringstream textStream;

        };

        //FIXME Don't know why, but programs threat all exceptions as Exception::Base type. May be we should
        //define constructors?

        //! Not critical. Simply instantiate
        class Warning : public Base
        {
        public:
            Warning() throw() : Base() {};
            Warning(Warning& _rvalue) : Base(_rvalue) throw() {};
            virtual ~Warning() throw()
            {
                std::cerr<<what();
            };
        };

        //! Reference to unexistent object was requested
        class ObjectNotFound : public Base
        {
        public:
            ObjectNotFound() throw() : Base() {};
            ObjectNotFound(ObjectNotFound& _rvalue) : Base(_rvalue) throw() {};
            virtual ~ObjectNotFound() throw();
        }; 
        
        //! Trying to add already existent element
        class ElementExists  : public Base
        {
        public:
            ElementExists() throw() : Base() {};
            ElementExists(ElementExists& _rvalue) : Base(_rvalue) throw() {};
            virtual ~ElementExists() throw();
        }; 

        //! Multiple elements exist, but onlyone allowed; ex: parallel links between neurons are not allowed
        class MultipleOccurance  : public Base
        {
        public:
            MultipleOccurance() throw() : Base() {};
            MultipleOccurance(MultipleOccurance& _rvalue) : Base(_rvalue) throw() {};
            virtual ~MultipleOccurance() throw();
        }; 

        //! Count of elements mismatch
        class SizeMismatch  : public Base
        {
        public:
            SizeMismatch() throw() : Base() {};
            SizeMismatch(SizeMismatch& _rvalue) : Base(_rvalue) throw() {};
            virtual ~SizeMismatch() throw();
        }; 

        //! Argument out of range
        class RangeMismatch  : public Base
        {
        public:
            RangeMismatch() throw() : Base() {};
            RangeMismatch(RangeMismatch& _rvalue) : Base(_rvalue) throw() {};
            virtual ~RangeMismatch() throw();
        }; 

        //! Requested not computed value
        class NotReady  : public Base
        {
        public:
            NotReady() throw() : Base() {};
            NotReady(NotReady& _rvalue) : Base(_rvalue) throw() {};
            virtual ~NotReady() throw();
        }; 

        //! Exceptionfor raising on filesystem failures (missing file etc.) 
        class FilesystemError  : public Base
        {
        public:
            FilesystemError() throw() : Base() {};
            FilesystemError(FilesystemError& _rvalue) : Base(_rvalue) throw() {};
            virtual ~FilesystemError() throw();
        }; 

        //! It's imposible in our universe!
        class Unbelievable  : public Base
        {
        public:
            Unbelievable() throw() : Base() {};
            Unbelievable(Unbelievable& _rvalue) : Base(_rvalue) throw() {};
            virtual ~Unbelievable() throw();
        }; 

    }; //Exception

}; //pann

#endif
