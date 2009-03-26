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
        template<class E, class T>
            E const & operator<<(E & _e, const T& _value) throw()
        {
            _e.textStream << _value;

            return _e;
        };

        //! Basic class for every exception
        class Base : public std::exception
        {
        public:
            Base() throw();
            Base(const Base& _rvalue) throw();
            virtual ~Base() throw();
            virtual const char* what() const throw();

        protected:
            std::ostringstream textStream;

        private:
            template<class E, class T>
                friend E const & operator<<(E const & _e, const T& _value) throw();
        };

        //! Not critical. Simply instantiate
        class Warning : public Base
        {
        public:
            Warning() throw() : Base() {};
            Warning(const Warning& _rvalue) throw() : Base(_rvalue) {};
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
            ObjectNotFound(const ObjectNotFound& _rvalue) throw() : Base(_rvalue) {};
            virtual ~ObjectNotFound() throw() {};
        }; 
        
        //! Trying to add already existent element
        class ElementExists  : public Base
        {
        public:
            ElementExists() throw() : Base() {};
            ElementExists(const ElementExists& _rvalue) throw() : Base(_rvalue) {};
            virtual ~ElementExists() throw() {};
        }; 

        //! Multiple elements exist, but onlyone allowed; ex: parallel links between neurons are not allowed
        class MultipleOccurance  : public Base
        {
        public:
            MultipleOccurance() throw() : Base() {};
            MultipleOccurance(const MultipleOccurance& _rvalue) throw() : Base(_rvalue) {};
            virtual ~MultipleOccurance() throw() {};
        }; 

        //! Count of elements mismatch
        class SizeMismatch  : public Base
        {
        public:
            SizeMismatch() throw() : Base() {};
            SizeMismatch(const SizeMismatch& _rvalue) throw() : Base(_rvalue) {};
            virtual ~SizeMismatch() throw() {};
        }; 

        //! Argument out of range
        class RangeMismatch  : public Base
        {
        public:
            RangeMismatch() throw() : Base() {};
            RangeMismatch(const RangeMismatch& _rvalue) throw() : Base(_rvalue) {};
            virtual ~RangeMismatch() throw() {};
        }; 

        //! Requested not computed value
        class NotReady  : public Base
        {
        public:
            NotReady() throw() : Base() {};
            NotReady(const NotReady& _rvalue) throw() : Base(_rvalue) {};
            virtual ~NotReady() throw() {};
        }; 

        //! Exceptionfor raising on filesystem failures (missing file etc.) 
        class FilesystemError  : public Base
        {
        public:
            FilesystemError() throw() : Base() {};
            FilesystemError(const FilesystemError& _rvalue) throw() : Base(_rvalue) {};
            virtual ~FilesystemError() throw() {};
        }; 

        //! It's imposible in our universe!
        class Unbelievable  : public Base
        {
        public:
            Unbelievable() throw() : Base() {};
            Unbelievable(const Unbelievable& _rvalue) throw() : Base(_rvalue) {};
            virtual ~Unbelievable() throw() {};
        }; 

    }; //Exception

}; //pann

#endif
