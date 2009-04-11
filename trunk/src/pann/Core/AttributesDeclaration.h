#ifndef ATTRIBUTESDECLARATION_H
#define ATTRIBUTESDECLARATION_H

#include "Attributes.h"

namespace pann
{
    namespace AttributesDeclaration
    {
        const AttributeHash OpenGl                              = hash("OpenGl");
        const AttributeHash CommonLearningParameters            = hash("CommonLearningParameters");
        const AttributeHash AlgorithmSpecificLearningParameters = hash("AlgorithmSpecificLearningParameters");
        const AttributeHash Other                               = hash("Other");
    }; //AttributesDeclaration

    namespace OpenGlHint
    {
        using namespace AttributesDeclaration;

        const AttributeName color_r = {
            hash("color_r"),
            OpenGl
        };
        const AttributeName color_g = {
            hash("color_g"),
            OpenGl
        };
        const AttributeName color_b = {
            hash("color_b"),
            OpenGl
        };
        const AttributeName coord_x = {
            hash("coord_x"),
            OpenGl
        };
        const AttributeName coord_y = {
            hash("coord_y"),
            OpenGl
        };
        const AttributeName coord_z = {
            hash("coord_z"),
            OpenGl
        };
    }; //OpenGlHint

}; //pann

#endif

