#include "pann.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

int main(int argc, char **argv)
{
    vector<Float> vec;
    vec +=  10, 10, 10,
		   0  ,  0,  0,
		   0  ,  0,  0,
		    13, 13, 13;
    valarray<Float> varr(vec.size());

    cout<<"Original valarray\n";
    for(unsigned i = 0; i < vec.size(); ++i)
    {
        varr[i] = vec[i];
        cout<<varr[i]<<' ';
    }
    cout<<endl;

    Image bmp1(2, 2, varr);

    valarray<Float> res1 = bmp1.getAverageValarray();
    cout<<"Average valarray\n";
    for(unsigned i = 0; i < res1.size(); ++i)
        cout<<res1[i]<<' ';
    cout<<endl;

    valarray<Float> res2 = bmp1.getCompositeValarray();
    cout<<"Composite valarray\n";
    for(unsigned i = 0; i < res2.size(); ++i)
        cout<<res2[i]<<' ';
    cout<<endl;

    if(argc > 1)
    {
        Image bmp = ImageIo::readImage(argv[1]);

        valarray<Float> res = bmp.getAverageValarray();
        cout<<"BIG average valarray\n";
        for(unsigned i = 0; i < res.size(); ++i)
            cout<<res[i]<<' ';
        cout<<endl;

        valarray<Float> res2 = bmp.getCompositeValarray();
        cout<<"BIG composite valarray\n";
        for(unsigned i = 0; i < res2.size(); ++i)
            cout<<res2[i]<<' ';
        cout<<endl;
    }


	ImageIo::writeImage(bmp1,"1.pgm",ImageIo::PGM);

    return 0;
}

