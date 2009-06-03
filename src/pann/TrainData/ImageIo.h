#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h" 

#include "Image.h"

namespace pann
{
    class ImageIo
    {
    public:
        /**
         * Reads image, determines it's format and calls corresponding reader
         * @param _filename Image file to read from
         * @return @see Image object
         */
        static Image readImage(const std::string& _filename);

    private:
        ImageIo();
        ~ImageIo();

        static Image readP5P6(const std::string& _filename);
    };

}; //pann

#endif

