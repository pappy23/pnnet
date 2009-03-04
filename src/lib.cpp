#include "lib.h"
#include <boost/any.hpp>

void print_hello()
{
    boost::any a = 5;
    std::cout<<"Hello\n"<<boost::any_cast<int>(a)<<std::endl;
}
