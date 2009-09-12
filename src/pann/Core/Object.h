#ifndef PANN_CORE_OBJECT_H_INCLUDES
#define PANN_CORE_OBJECT_H_INCLUDES

#include "Includes/Std.h"
#include "Includes/BoostSerialization.h"

#include "Exception.h"
#include "Attributes.h"

using std::map;
using boost::shared_ptr;
using boost::dynamic_pointer_cast;

namespace pann
{
    class Object
    {
    public:
        Object() {};
        virtual ~Object() {};
/*
        AttributesPtr& getPtr(HashType _group)
        {
            return attributes[_group];
        };

        const AttributesPtr& getPtr(HashType _group) const
        {
            return attributes[_group];
        };
*/
        template<class T>
        T& get()
        {
            AttributesPtr& raw_ptr = attributes[T::getHash()];
            shared_ptr<T> casted_ptr = dynamic_pointer_cast<T, Attributes>(raw_ptr);
            //Optimization is possible

            if(!casted_ptr)
            {
                T* ptr = new T();
                raw_ptr.reset(ptr);
                return *ptr;
            } else {
                return *casted_ptr;
            }
        };

        template<class T>
        const T& get() const
        {
            AttributesPtr& raw_ptr = attributes[T::getHash()];
            shared_ptr<T> casted_ptr = dynamic_pointer_cast<T, Attributes>(raw_ptr);

            if(!casted_ptr)
            {
                throw Exception()<<"Attributes access exception\n";
            } else {
                return *casted_ptr;
            }
        };

        void clearAttributes()
        {
            attributes.clear();
        };

    private:
        map<HashType, AttributesPtr> mutable attributes;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(attributes);
            };
    }; //Object

}; //pann

#endif //PANN_CORE_OBJECT_H_INCLUDES

