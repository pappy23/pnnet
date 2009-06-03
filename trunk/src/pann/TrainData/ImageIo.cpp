
#include "ImageIo.h"

using namespace std;
using namespace boost;

namespace pann
{
    Image
    ImageIo::readImage(const std::string& _filename)
    {
        ifstream in(_filename.c_str());

        if(!in)
            throw IoError()<<"Can't open file "<<_filename.c_str()<<"\n";

        //What happening??

        char str[1024];
        in >> str;

        while(str[0] == '#')
        {
            in.getline(str,1024);
            in >> str;
        }

        in.close();

        //Continue

        switch (str[1])
        {
        case '5' :
        case '6' :
            return readP5P6(_filename);
            break;
        default:
            throw IoError()<<"Format not supported\n";
        }

        //Never reaches this point
        return Image();
    } //readFile

    Image
    ImageIo::readP5P6(const std::string& _filename)
    {
        ifstream in(_filename.c_str(), ios::binary);

        if(!in)
            throw IoError()<<"Can't open file "<<_filename.c_str()<<"\n";

        vector<string> params;

        char buf[1024];
        for(unsigned i = 0; i < 4; ++i)
        {
            in >> buf;
            while(buf[0] == '#')
            {
                in.getline(buf,1024);
                in >> buf;
            }
            params.push_back(buf);
        }

        unsigned w, h, depth;

        try {
            w = lexical_cast<unsigned>(params[1].c_str());
            h = lexical_cast<unsigned>(params[2].c_str());
            depth = unsigned(lexical_cast<Float>(params[3].c_str()) / 255.0);
        } catch(bad_lexical_cast&) {
            throw IoError()<<"Bad lexical cast\n";
        }

        if ("P6" == params[0])
            depth *= 3;

        valarray<Float> va(w * h * depth);

        char c;
        in.get(c);
        for (unsigned i = 0; i < w * h; ++i)
            for (unsigned j = 0; j < depth; ++j)
            {
                c = in.get();
                va[i * depth + j] = c;
            }

        in.close();

        return Image(w, h, va);
    } //readP5P6

}; //pann
