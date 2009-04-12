#ifndef OPENGLATTRIBUTES_H
#define OPENGLATTRIBUTES_H

#include "Object.h"

namespace pann
{
    namespace OpenGlAttributes
    {
        const AttributeName color_r = hash("color_r", "OpenGL");
        const AttributeName color_g = hash("color_g", "OpenGL");
        const AttributeName color_b = hash("color_b", "OpenGL");
        const AttributeName coord_x = hash("coord_x", "OpenGL");
        const AttributeName coord_y = hash("coord_y", "OpenGL");
        const AttributeName coord_z = hash("coord_z", "OpenGL");
    }; //OpenGlAttributes

}; //pann

#endif

