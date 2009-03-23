#ifndef OPENGLHINT_H
#define OPENGLHINT_H

#include "Includes.h"

namespace pann
{
    class Point3d
    {
    public:
        Float x, y, z;
    };

    class Color
    {
    public:
        char r, g, b;
    };

    class OpenGLHint
    {
    public:
        OpenGLHint()
        {
            color.r = color.g = color.b = 0;
            point.x = point.y = point.z = 0;
        };

        Color color;
        Point3d point;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_NVP(point.x)
             & BOOST_SERIALIZATION_NVP(point.y)
             & BOOST_SERIALIZATION_NVP(point.z)
             & BOOST_SERIALIZATION_NVP(color.r)
             & BOOST_SERIALIZATION_NVP(color.g)
             & BOOST_SERIALIZATION_NVP(color.b);
        };
    };

}; //pann

BOOST_CLASS_TRACKING(pann::OpenGLHint, boost::serialization::track_never);

#endif //OPENGLHINT_H

