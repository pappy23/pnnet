//Net.cpp

#include "Net.h"

using namespace std;

namespace pann
{
    Net::Net()
    {
        Net::Net(0);
    } //Net

    Net::Net(int _threads)
    {
        lastNeuronId = 0;
        lastWeightId = 0;
        setThreadCount(_threads);
    } //Net

    Net::~Net()
    {
    } //~Net

    int Net::getThreadCount()
    {
        return threadCount;
    } //getThreadCount

    void Net::setThreadCount(int _threads)
    {
        cache.touch();

        if(_threads == 0)
        {
            threadCount = boost::thread::hardware_concurrency();
            return;
        }

        if(_threads < 1 || _threads > 64)
            throw Exception::RangeMismatch()<<"Net::run(): currently only up to 5 concurrent threads supported\n";

        threadCount = _threads;
    } //setThreadCount

    NeuronIter Net::findNeuron(int _neuronId)
    {
        NeuronIter iter = neurons.find(_neuronId);
        if(neurons.end() == iter)
            throw Exception::ObjectNotFound()<<"findNeuron(): Neuron "<<_neuronId<<" not found\n";

        return iter;
    } //isNeuronExist

    void Net::formatFront(vector<NeuronIter>& _raw)
    {
        cache.data.push_back( NetCache::FrontType() );
        NetCache::FrontType& tasks = cache.data[cache.data.size() - 1];

        for(int i = 0; i < threadCount; i++)
            tasks.push_back( vector<NeuronIter>() );

        sort(_raw.begin(), _raw.end(), NeuronIterCompare());
        vector<NeuronIter>::iterator it = unique(_raw.begin(), _raw.end(), NeuronIterCompare::equal);
        _raw.resize( it - _raw.begin() );

        for(UINT i = 0; i < _raw.size(); ++i)
            tasks[_raw[i]->second.getOwnerThread() % threadCount].push_back(_raw[i]);

    } //formatFront

    int Net::addNeuron(ActivationFunction::Base* _activationFunction)
    {
        cache.touch();

        pair<NeuronIter, bool> result = neurons.insert( pair<int, Neuron>(lastNeuronId, Neuron(_activationFunction)) );

        if(!result.second)
            throw Exception::ElementExists()<<"Net::addNeuron(): insertion of neuron "<<lastNeuronId<<" failed\n";

        return lastNeuronId++;
    } //addNeuron

    int Net::addInputNeuron()
    {
        int neuronId = addNeuron(ActivationFunction::Linear::Instance());
        setNeuronRole(neuronId, Net::InputNeuron);

        return neuronId;
    } //addInputNeuron

    int Net::addOutputNeuron(ActivationFunction::Base* _activationFunction)
    {
        int neuronId = addNeuron(_activationFunction);
        setNeuronRole(neuronId, Net::OutputNeuron);

        return neuronId;
    } //addOutputNeuron

    void Net::delNeuron(int _neuronId)
    {
        cache.touch();

        NeuronIter n = findNeuron(_neuronId);

        //Delete all connections to/from current neuron
        for(list<Link>::iterator link_iter = n->second.links.begin(); link_iter != n->second.links.end(); )
        {
            //We will delete link, so we can't use link_iter to get access to Link object
            //Copy Link attributes into local variables
            NeuronIter to = link_iter->getToIter();
            Link::Direction dir = link_iter->getDirection();
            
            //Go to next Link (see for loop - it is without ++ statement)
            link_iter++;

            if(dir == Link::in)
                delConnection(to->first, n->first);
            else
                delConnection(n->first, to->first);
        }

        //Actually delete Neuron object
        if( !neurons.erase(_neuronId) )
            throw Exception::ObjectNotFound()<<"Net::delNeuron(): can't delete neuron "<<_neuronId<<"\n";
    } //delNeuron

    void Net::setNeuronRole(int _neuronId, NeuronRole _newRole)
    {
        cache.touch();

        NeuronIter iter = findNeuron(_neuronId);

        list< NeuronIter >::iterator inputIter = find(inputNeurons.begin(), inputNeurons.end(), iter);
        list< NeuronIter >::iterator outputIter = find(outputNeurons.begin(), outputNeurons.end(), iter);

        switch(_newRole)
        {
            case InputNeuron:
                if(outputIter != outputNeurons.end())
                    outputNeurons.erase(outputIter);
                if(inputIter == inputNeurons.end())
                    inputNeurons.push_back(iter);
                break;
            case OutputNeuron:
                if(inputIter != inputNeurons.end())
                    inputNeurons.erase(inputIter);
                if(outputIter == outputNeurons.end())
                    outputNeurons.push_back(iter);
                break;
            case WorkNeuron:
                if(inputIter != inputNeurons.end())
                    inputNeurons.erase(inputIter);
                if(outputIter != outputNeurons.end())
                    outputNeurons.erase(outputIter);
                break;
        }
    } //setNeuronRole

    Net::NeuronRole Net::getNeuronRole(int _neuronId)
    {
        /*
         * 0 - work neuron
         * 1 - work+input
         * 2 - work+output
         */
        int role = 0;

        NeuronIter iter = findNeuron(_neuronId);

        if(find(inputNeurons.begin(), inputNeurons.end(), iter) != inputNeurons.end())
            role+=1;
        if(find(outputNeurons.begin(), outputNeurons.end(), iter) != outputNeurons.end())
            role+=2;

        return (NeuronRole)role;
    } //getNeuronRole

    void Net::setNeuronOwner(int _neuron, int _owner)
    {
        findNeuron(_neuron)->second.setOwnerThread(_owner);
    } //setNeuronOwner

    int Net::getNeuronOwner(int _neuron)
    {
        return findNeuron(_neuron)->second.getOwnerThread();
    } //getNeuronOwner

    void Net::addConnection(int _from, int _to, Float _weightValue)
    {
        cache.touch();

        NeuronIter from = findNeuron(_from);
        NeuronIter to = findNeuron(_to);

        pair<WeightIter, bool> result = weights.insert( pair<int, Weight>(lastWeightId++, Weight(_weightValue)) );
        if(!result.second)
            throw Exception::ElementExists()<<"Net::addWeight(): insertion of new weight failed\n";

        from->second.links.push_back( Link(to, Link::out, result.first) );
        to->second.links.push_back( Link(from, Link::in, result.first) );

        result.first->second.usageCount = 2;
    } //addConnection

    void Net::delConnection(int _from, int _to)
    {
        cache.touch();
        
        NeuronIter from_niter = findNeuron(_from);
        NeuronIter to_niter   = findNeuron(_to);

        /* Short introduction:
         * Neuron_from               Neuron_to
         *  Link                      Link
         *    to =>Neuron2              to =>Neuron1
         *    w  =>weight1              w  =>weight1
         *    dir=>out                  dir=>in
         */

        //Find correspondent Links in neurons
        list<Link>::iterator from_liter = from_niter->second.findLink(to_niter, Link::out);
        list<Link>::iterator to_liter = to_niter->second.findLink(from_niter, Link::in);

        //weight1 (see picture) must be common for both Link objects
        if(from_liter->getWeightIter() != to_liter->getWeightIter())
            throw Exception::Unbelievable()<<"Net::delConnection(): symmetric links don't share weight\n";

        //We will delete Link objects and iterators to common weight will be lost
        WeightIter w_iter = from_liter->getWeightIter();

        //Actually delete Link objects from Neuron_to and Neuron_from
        from_niter->second.links.erase(from_liter);
        to_niter->second.links.erase(to_liter);

        //Delete weight object if it no more used
        if( (w_iter->second.usageCount -= 2) == 0) 
            weights.erase(w_iter->first);

    } //delConnection

    std::vector<int> Net::getInputMap()
    {
        vector<int> result;

        BOOST_FOREACH( NeuronIter iter, inputNeurons)
            result.push_back(iter->first);

        return result;
    } //getInputMap

    std::vector<int> Net::getOutputMap()
    {
        vector<int> result;

        BOOST_FOREACH( NeuronIter iter, outputNeurons)
            result.push_back(iter->first);

        return result;
    } //getOutputMap

    void Net::setInput(const vector<Float>& _input)
    {
        if(_input.size() < inputNeurons.size())
            throw Exception::SizeMismatch()<<"setInput(): Supplied input size is smaller "
                                                          "then number of input neurons\n";

        if(_input.size() > inputNeurons.size())
            Exception::Warning()<<"setInput(): Input size is bigger then input neurons count. "
                                               "Check getInputMap() output\n";

        int i = 0;
        BOOST_FOREACH( NeuronIter iter, inputNeurons)
            iter->second.receptiveField += _input[i++];
    } //setInput

    vector<Float> Net::getOutput()
    {
        vector<Float> result;
        BOOST_FOREACH( NeuronIter iter, outputNeurons)
            result.push_back(iter->second.activationValue);

        return result;
    } //setInput

    /*
     * This function updates cache and does
     * forward propagation through neural network
     * Be extremely careful!
     */
    void Net::run(Runner* _runner)
    {
        //Here we will place neuron's IDs that will become front, with duplicates
        vector<NeuronIter> rawFront;

        /*
         * Function operates with "hops" attribute of every Neuron
         * to build adequate cache. If cache is already up2date, this
         * map<> remains empty
         * Unfortunetly, map<int, Neuron>::iterator doesn't have operator< , so
         * we shold write own comparison class for hops<>. I placed it to Utils.h
         */
        map<NeuronIter, int, NeuronIterCompare> hops;

        //If cache is not up2date, flush it and fill again
        if( !cache.isOk() )
        {
            cache.flush();

            //Put inputNeurons to front
            if( _runner->getDirection() == ForwardRun)
            {
                BOOST_FOREACH( NeuronIter iter, inputNeurons )
                {
                    rawFront.push_back(iter);
                    hops[iter] = 1;
                }
            } else {
                //FIXME Backward run is impossible. Cache is built for forward run only
                BOOST_FOREACH( NeuronIter iter, outputNeurons )
                {
                    rawFront.push_back(iter);
                    hops[iter] = 1;
                }
            }

            formatFront(rawFront);
        }

        /*
         * Cache looks like this:
         *
         * vector<FrontType> cache.data
         *     |
         *     |-(0) vector<ThreadTaskType>      <-- * front pointer points to this vector
         *     |-(1) vector<ThreadTaskType>
         *     |-(...)
         *     |-(number_of_layers) vector<ThreadTaskType>
         *                          |
         *                          |-(0) vector<Neuron*> Target neurons for thread1
         *                          |-(1) vector<Neuron*> Target neurons for thread2
         *
         *  At this point cache.data(0) is the only record and it contains input neurons
         */

        int layer = 0;
        do
        {
            //At first iteration front points to first 'layer', derived from rawFront
            NetCache::FrontType& front = cache.data[layer++];

            boost::thread_group threadPool;

            //front is ready, lets start our pretty threads =)
            for(int i = 0; i < threadCount; i++)
                if(front[i].size() > 0)
                    threadPool.add_thread( new boost::thread(this->threadBase, _runner, front[i]) );
           //FIXME: put parameters by boost::ref rather then by copying

            if( !cache.isOk() )
            {
                /*
                 * We have better prepare next front
                 * This block is done one time per cache generation and it
                 * is executed by main() thread
                 *
                 * At first iteration, if you remember, vector<int> _raw contains unique inputNeurons indexes
                 */
                int nCount = (int) rawFront.size();
                for(int i = 0; i < nCount; ++i)
                {
                    //pop_front emulation
                    NeuronIter currentNeuronIter = rawFront[0];
                    rawFront.erase( rawFront.begin() );

                    //ok, we've got cur_neuron. We will iterate through his Out links
                    //and push_back their opposite sides to rawFront
                    BOOST_FOREACH( Link& link, currentNeuronIter->second.links )
                    {
                        //Only feedforward links
                        if(link.getDirection() == Link::in)
                            continue;

                        /*
                         * Short comment. Consider following topology (hops are in brackets):
                         *   +(0)    <-- output          +(0)             +(3)    <-- front(3)
                         *  / \                         / \              / \
                         * +(0)+(0)         ======>    +(0)+(0)  ====>  +(2)+(2)  <-- front(2)
                         *  \ /           iteration1    \ /        N     \ /
                         *   +(0)  <-- input             +(1)             +(1)    <-- front on iteration1
                         *
                         *   For current neuron (C) and other neuron (T), hops might be:
                         *   T = 0  - T-neuron is fresh. We will set T=C+1
                         *   T = N, N < C - it is recurrent link. Dont touch T and dont place it into rawFront
                         *   T = C  - it is stupid recursive topology. Currently unsupported. Raise exception
                         *   T = C + 1 - T already hadled. Silently ignore T. We can add T to rawFront
                         *   T > C + 1 - impossible. Somebody changed hops by hand and didn't touch cache or
                         *               after last cache generation algorithm didn't set neuron's hops to zero
                         */

                        //Assume that when cache becomes coherent, all neuron[hops] vars become zero
                        if(hops[link.getToIter()] == 0)
                            hops[link.getToIter()] = hops[currentNeuronIter] + link.getLatency();

                        if(hops[link.getToIter()] == hops[currentNeuronIter] + 1)
                            rawFront.push_back(link.getToIter()); 

                        if(hops[link.getToIter()] == hops[currentNeuronIter])
                            throw Exception::Unbelievable()<<"Net::run(): cur_neuron.hops == to.hops. "
                                                                "There is no support for such topologies yet\n";
                    } //BOOST_FOREACH( Link )

                } //rawFront iteration ( Neuron )

                //new rawFront formed
                formatFront(rawFront);

            } // if( !cache.isOk() )

            //wait for threads to finish
            threadPool.join_all();
 
        } while( (!cache.isOk() && rawFront.size() > 0) || (cache.isOk() && layer < cache.data.size() - 1) );

        //We rebuilded cache
        if(!cache.isOk())
            cache.fixed();

    } //run

}; //pann

