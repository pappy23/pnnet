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
            ar & point.x;
            ar & point.y;
            ar & point.z;
            ar & color.r;
            ar & color.g;
            ar & color.b;
        };
    };
}; //pann

#endif //OPENGLHINT_H

