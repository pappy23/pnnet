#include <iostream>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;
using namespace boost;

class A
{
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
        ar & a;
        }

    public:
        int a;
};

int main()
{
    A obj;
    obj.a = 5;

    {
        ofstream ofs("serialization_test.txt");
        boost::archive::text_oarchive oa(ofs);
        oa<<obj;
    }


    A obj2;

    {
        ifstream ifs("serialization_test.txt");
        boost::archive::text_iarchive ia(ifs);
        ia >> obj2;
    }

    cout<<"Result: "<<obj2.a<<endl;

    return 0;
}

