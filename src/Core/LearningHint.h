#ifndef LEARNINGHINT_H
#define LEARNINGHINT_H

#include "Includes.h"
#include "Exception.h"
#include "LMS.h"

namespace pann
{
    namespace LearningHint
    {
        class Base
        {
        public:
            Base() { };
            virtual ~Base() { };

            virtual unsigned getTypeId() = 0;

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    //Do nothing in base class
                };
        };

        class Null
        {
        public:
            Null();
            virtual ~Null();

            virtual unsigned getTypeId();

            /* Serialization */
        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    //Do nothing
                };
        };

        Base* getById(unsigned _id);
    };

}; //pann

#endif

