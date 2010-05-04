#ifndef PANN_ATTRIBUTES_OPENGLATTRIBUTES_H_INCLUDED
#define PANN_ATTRIBUTES_OPENGLATTRIBUTES_H_INCLUDED

#include "Core/Attributes.h"

namespace pann {
    /**
     * Attributes used in neurons to draw network model
     * in pann_viewer
     */
    class OpenGlAttributes : public Attributes
    {
    public:
        OpenGlAttributes() : r(0), g(0), b(0), x(0), y(0), z(0) {};
        virtual ~OpenGlAttributes() {};

        static const HashT getHash()
        {
            static HashT groupName = hash("OpenGlAttributes");
            return groupName;
        };

    public:
        unsigned char r, g, b; //Color
        signed int x, y, z; //Coordinates

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<OpenGlAttributes, Attributes>(
                    static_cast<OpenGlAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(x)
                & BOOST_SERIALIZATION_NVP(y)
                & BOOST_SERIALIZATION_NVP(z)
                & BOOST_SERIALIZATION_NVP(r)
                & BOOST_SERIALIZATION_NVP(g)
                & BOOST_SERIALIZATION_NVP(b);
            };

    }; //OpenGlAttributes
    REGISTER_ATTRIBUTES_H(OpenGlAttributes);

}; //pann

#endif //PANN_ATTRIBUTES_OPENGLATTRIBUTES_H_INCLUDED

