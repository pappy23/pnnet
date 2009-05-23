
#include "pann.h"

using namespace pann;
using namespace std;
using namespace boost;

int main()
{
    //
    //Weight
    //

    shared_ptr<Weight> w(new Weight(0.5));
    w->incUsageCount();

    w->setValue(w->getValue() + w->getUsageCount());

    {
        boost::mutex::scoped_lock lock(w->getMutex());
    }

    //TODO: test serialization    

    //
    //Link
    //
    shared_ptr<Neuron> n1(new Neuron(ActivationFunction::TanH::Instance()));
    Link l1(n1, w);
    Link l2(l1);
    {
        Link l3 = l2;
    }
    
    cout<<l2.getWeight()->getUsageCount()<<" "<<w.use_count()<<endl;

    return 0;
}

