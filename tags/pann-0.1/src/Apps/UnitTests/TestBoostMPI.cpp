#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>

namespace mpi = boost::mpi;
using namespace std;

int main(int argc, char* argv[]) 
{
    mpi::environment env(argc, argv);
    mpi::communicator world;

    std::cout<<"I am process "<<world.rank()<<" of "<<world.size()<<'.'<<endl;

    int a = 0, b;
    while(1)
    {
        a--;
        b = a; 
    }

    std::cout<<b;

    return 0;
}

