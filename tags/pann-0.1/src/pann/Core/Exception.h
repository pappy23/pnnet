/**
 * @file
 * Defines and implements all exception related stuff
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Includes/Std.h"

namespace pann
{
    /**
     * Basic class for all exceptions
     * Use case: throw(Exception()<<"Hello"<<','<<" world!"<<5<<'\n')
     *      catch(Exception& e)
     * Don't forget to declare your CoolException, derived from Exception
     */
    class Exception : public std::exception
    {
    public:
        Exception() {};

        Exception(const Exception& _rhs )
        {
            msg = _rhs.msg;
        }

        virtual ~Exception() throw() {};

        virtual const char * what() const throw()
        {
            return msg.c_str();
        }

        template<typename T>
        Exception& operator<<(const T& _arg)
        {
            std::stringstream ss;
            ss << _arg;
            accumulate(ss.str());

            return *this;
        }

    protected:
        virtual void accumulate(const std::string& _arg)
        {
            msg += _arg;
        }

    private:
        std::string msg;
    }; //Exception

    /// Nothing critical
    class Warning : public Exception
    {
    protected:
        virtual void accumulate(const std::string& _arg)
        {
            std::cerr<<_arg;
        }
    }; //Warning

    /// Information for user
    class Info : public Exception
    {
    protected:
        virtual void accumulate(const std::string& _arg)
        {
            std::cout<<_arg;
        }
    }; //Info

    /// Debug
    class Debug : public Info {};

    /// Reference to unexistent object was requested
    class NotFound : public Exception {}; 
    
    /// Count of elements mismatch
    class SizeMismatch : public Exception {}; 

    /// Exceptionfor raising on filesystem failures (missing file etc.) 
    class IoError : public Exception {}; 

    /// It's imposible in our universe!
    // USE base class - Exception instead 
    //class Unbelievable : public Exception {}; 

}; //pann

#endif

