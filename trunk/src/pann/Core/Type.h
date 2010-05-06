/*
 * @file
 * Custom types declarations
 */

#ifndef PANN_CORE_TYPE_H_INCLUDED
#define PANN_CORE_TYPE_H_INCLUDED

#include "Includes/Std.h"
#include <boost/functional/hash.hpp>
#include <boost/shared_ptr.hpp>

namespace pann
{
    typedef double Float;
    const Float inf = std::numeric_limits<Float>::infinity();

    typedef std::size_t Hash;

    /**
     * Hasher
     * @param _name Readable name of attributes group
     * @return Unique integer hash value
     */
    inline Hash hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    }; //hash

}; //pann

/**
 * Use case: ADD_PTR_TYPEDEF(Neuron)
 */
#define ADD_PTR_TYPEDEF(C) \
    class C; \
    typedef boost::shared_ptr<C> C##Ptr; \
    typedef boost::shared_ptr<const C> C##ConstPtr;

#endif //PANN_CORE_TYPE_H_INCLUDED

#define SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(CLASS, BASE) \
    friend class boost::serialization::access; \
    template<class Archive> \
    void serialize(Archive & ar, const unsigned int version) \
    { \
        boost::serialization::void_cast_register<CLASS, BASE>( \
            static_cast<CLASS*>(NULL), \
            static_cast<BASE*>(NULL)); \
    }; \
    public: \
        static BASE##Ptr Instance() \
        { \
            static BASE##Ptr self(new CLASS()); \
            return self; \
        };

#define SINGLETON_SKELETON(CLASS, BASE) \
    CLASS() {}; \
    SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(CLASS, BASE);

//Register singleton in .h file and don't use .cpp
/*
#define REGISTER_SINGLETON(C, T) \
    BOOST_CLASS_EXPORT(pann::C) \
    const pann::T##Ptr C##Register = pann::C::Instance();
*/

//Split registration
#define REGISTER_SINGLETON_H(C) \
    int register_singleton_##C(); \
    const int register_singleton_##C##_result = register_singleton_##C();

#define REGISTER_SINGLETON_CPP(C) \
    BOOST_CLASS_EXPORT(pann::C) \
    namespace pann { \
    int register_singleton_##C() \
    { \
        C::Instance(); \
        return 0; \
    }; \
    };

