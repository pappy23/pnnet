#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h" 

#include "Image.h"
#include "Squash.h"

using std::string;

namespace pann
{
    class ImageIo
    {
    public:
        enum FileType { PGM, PPM };
        /**
         * Reads image, determines it's format and calls corresponding reader
         * @param _filename Image file to read from
         * @return @see Image object
         */
        static Image readImage(const string& _filename);

        /**
         * Writes image to file
         * @param _img Image to write
         * @param _filename Filename
         * @param _type File format (@see FileType)
         */
        static void writeImage(const Image& _img, const string& _filename, FileType _type);

    private:
        ImageIo();
        ~ImageIo();

        static Image readP5P6(const string& _filename);
        static void writeP5(const Image& _img, const string& _filename);
    };

}; //pann

#endif

