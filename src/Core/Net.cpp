//Net.cpp

#include "Net.h"

using namespace std;

namespace pann
{
    Net::Net()
    {
        Net::Net(0);
    } //Net

    Net::Net(unsigned _threads)
    {
        lastNeuronId = 0;
        setThreadCount(_threads);
        learningHint = 0;
        biasId = addNeuron(ActivationFunction::Linear::Instance());
        addConnection(biasId, biasId, 1);
    } //Net

    Net::~Net()
    {
        if(!learningHint)
            delete learningHint;
    } //~Net

    unsigned
    Net::getThreadCount() const
    {
        return threadCount;
    } //getThreadCount

    void
    Net::setThreadCount(unsigned _threads)
    {
        cache.touch();

        if(_threads == 0)
        {
            threadCount = boost::thread::hardware_concurrency();
            return;
        }

        if(_threads < 1 || _threads > 64)
            throw Exception::RangeMismatch()<<"Net::run(): currently only up to 64 concurrent threads supported\n";

        threadCount = _threads;
    } //setThreadCount

    unsigned
    Net::addNeuron(ActivationFunction::Base* _activationFunction)
    {
        cache.touch();
        pair< map<unsigned, Neuron*>::iterator, bool > result = 
            neurons.insert( pair<unsigned, Neuron*>(lastNeuronId, new Neuron(_activationFunction)) );
        
        if( !result.second )
            throw Exception::ElementExists()<<"Net::addNeuron(): insertion of neuron "<<lastNeuronId<<" failed\n";

        return lastNeuronId++;
    } //addNeuron

    unsigned
    Net::addInputNeuron()
    {
        unsigned neuronId = addNeuron(ActivationFunction::Linear::Instance());
        setNeuronRole(neuronId, Net::InputNeuron);

        return neuronId;
    } //addInputNeuron

    void
    Net::delNeuron(unsigned _neuronId)
    {
        cache.touch();

        Neuron* n = findNeuron(_neuronId);

        //Delete all connections to/from current neuron
        for(list<Link>::iterator link_iter = n->links.begin(); link_iter != n->links.end(); )
        {
            //We will delete link, so we can't use link_iter to get access to Link object
            //Copy Link attributes to local variables
            Neuron* to = link_iter->getTo();
            Link::Direction dir = link_iter->getDirection();
            
            //Go to next Link (see for loop - it is without ++ statement)
            link_iter++;

            if(dir == Link::in)
                delConnection(to->getId(), _neuronId);
            else
                delConnection(_neuronId, to->getId());
        }

        //Actually delete Neuron object
        neurons.erase(n->getId());
        delete n;
    } //delNeuron

    void
    Net::setNeuronRole(unsigned _neuronId, NeuronRole _newRole)
    {
        cache.touch();

        Neuron* n = findNeuron(_neuronId);

        list<Neuron*>::iterator inputIter = find(inputNeurons.begin(), inputNeurons.end(), n);

        switch(_newRole)
        {
            case InputNeuron:
                if(inputIter == inputNeurons.end())
                    inputNeurons.push_back(n);
                break;
            case WorkNeuron:
                if(inputIter != inputNeurons.end())
                    inputNeurons.erase(inputIter);
                break;
        }
    } //setNeuronRole

    Net::NeuronRole
    Net::getNeuronRole(unsigned _neuronId) const
    {
        /*
         * 0 - work neuron
         * 1 - work+input
         */
        unsigned role = 0;

        const Neuron* n = findNeuron(_neuronId);

        if(find(inputNeurons.begin(), inputNeurons.end(), n) != inputNeurons.end())
            role+=1;

        return (NeuronRole)role;
    } //getNeuronRole

    void
    Net::addConnection(unsigned _from, unsigned _to, Float _weightValue)
    {
        cache.touch();

        Neuron* from = findNeuron(_from);
        Neuron* to = findNeuron(_to);

        Weight *w = new Weight(_weightValue);

        from->links.push_back( Link(to, Link::out, w) );
        to->links.push_back( Link(from, Link::in, w) );

        w->usageCount = 2;
    } //addConnection

    void
    Net::delConnection(unsigned _from, unsigned _to)
    {
        cache.touch();
        
        Neuron* from_neuron = findNeuron(_from);
        Neuron* to_neuron   = findNeuron(_to);

        /* Short unsignedroduction:
         * Neuron_from               Neuron_to
         *  Link                      Link
         *    to =>Neuron2              to =>Neuron1
         *    w  =>weight1              w  =>weight1
         *    dir=>out                  dir=>in
         */

        //Find correspondent Links in neurons
        list<Link>::iterator from_link = from_neuron->findLink(to_neuron, Link::out);
        list<Link>::iterator to_link = to_neuron->findLink(from_neuron, Link::in);

        //weight1 (see picture) must be common for both Link objects
        if(from_link->getWeight() != to_link->getWeight())
            throw Exception::Unbelievable()<<"Net::delConnection(): symmetric links don't share weight\n";

        //We will delete Link objects and pointers to common weight will be lost
        Weight* w = from_link->getWeight();

        //Actually delete Link objects from Neuron_to and Neuron_from
        from_neuron->links.erase(from_link);
        to_neuron->links.erase(to_link);

        //Delete weight object if it no more used
        if( (w->usageCount -= 2) == 0) 
            delete w;
    } //delConnection

    void
    Net::setNeuronOwner(unsigned _neuron, unsigned _owner)
    {
        findNeuron(_neuron)->setOwnerThread(_owner);
    } //setNeuronOwner

    unsigned
    Net::getNeuronOwner(unsigned _neuron) const
    {
        return findNeuron(_neuron)->getOwnerThread();
    } //getNeuronOwner

    std::vector<unsigned>
    Net::getInputMap() const
    {
        vector<unsigned> result;

        BOOST_FOREACH( Neuron* n, inputNeurons)
            result.push_back(n->getId());

        return result;
    } //getInputMap

    void
    Net::setInput(const valarray<Float>& _input)
    {
        if(_input.size() < inputNeurons.size())
            throw Exception::SizeMismatch()<<"setInput(): Supplied input size is smaller "
                                                          "then number of input neurons\n";

        if(_input.size() > inputNeurons.size())
            Exception::Warning()<<"setInput(): Input size is bigger then input neurons count. "
                                               "Check getInputMap() output\n";

        unsigned i = 0;
        BOOST_FOREACH( Neuron* n, inputNeurons)
            n->receptiveField += _input[i++];
    } //setInput

    map<unsigned, Float>
    Net::getOutput() const
    {
        map<unsigned, Float> result;

        if( !cache.isOk() )
            regenerateCache();

        if(cache.data.size() < 2)
            return result;

        BOOST_FOREACH( const NetCache::ThreadTaskType& task, cache.data[cache.data.size() - 2])
            BOOST_FOREACH( Neuron* n, task )
                result.insert(pair<unsigned, Float>(n->getId(), n->activationValue));

        return result;
    } //getOutput

    void
    Net::getOutput(valarray<Float>& _output) const
    {
        map<unsigned, Float> output = getOutput();
        _output.resize(output.size());

        unsigned i = 0;
        for(map<unsigned, Float>::const_iterator iter = output.begin(); iter != output.end(); ++iter)
            _output[i++] = iter->second;
    } //getOutput

    void
    Net::run(Runner* _runner)
    {
        if( !cache.isOk() )
            regenerateCache();

        boost::thread_group threadPool;
        boost::barrier barrier(threadCount);

        for(unsigned thread = 0; thread < threadCount; ++thread)
            threadPool.add_thread( new boost::thread(Net::threadBase, _runner, &cache, thread, &barrier) );
        
        //wait for threads to finish
        threadPool.join_all();
    } //run

    const NetCache& 
    Net::getCache() const
    {
        return cache;
    } //getCache

    const map<unsigned, Neuron*>& 
    Net::getNeurons() const
    {
        return neurons;
    } //getNeurons

    unsigned
    Net::getBiasId() const
    {
        return biasId;
    }; //getBiasId

    Neuron*
    Net::findNeuron(unsigned _neuronId)
    {
        map<unsigned, Neuron*>::iterator iter = neurons.find(_neuronId);
        if(neurons.end() == iter)
            throw Exception::ObjectNotFound()<<"findNeuron(): Neuron "<<_neuronId<<" not found\n";

        return iter->second;
    } //findNeuron

    const Neuron*
    Net::findNeuron(unsigned _neuronId) const
    {
        return const_cast<Net*>(this)->findNeuron(_neuronId);
    } //findNeuron

    void
    Net::formatFront(vector<Neuron*>& _raw) const
    {
        cache.data.push_back( NetCache::FrontType() );
        NetCache::FrontType& tasks = cache.data[cache.data.size() - 1];

        for(unsigned i = 0; i < threadCount; i++)
            tasks.push_back( vector<Neuron*>() );

        //sort(_raw.begin(), _raw.end(), NeuronIterCompare());
        sort(_raw.begin(), _raw.end()); //FIXME Caution!
        //vector<Neuron*>::iterator it = unique(_raw.begin(), _raw.end(), NeuronIterCompare::equal);
        vector<Neuron*>::iterator it = unique(_raw.begin(), _raw.end());
        _raw.resize( it - _raw.begin() );

        for(unsigned i = 0; i < _raw.size(); ++i)
            tasks[_raw[i]->getOwnerThread() % threadCount].push_back(_raw[i]);
    } //formatFront

    void
    Net::regenerateCache() const
    {
        cache.flush(); 

        //Here we will place neuron's IDs that will become front, with duplicates
        vector<Neuron*> rawFront;

        /*
         * Function operates with "hops" attribute of every Neuron
         * to build adequate cache.
         * Unfortunetly, map<unsigned, Neuron>::iterator doesn't have operator< , so
         * we shold write own comparison class for hops<>. I placed it to Utils.h
         */
        //map<Neuron*, unsigned, NeuronIterCompare> hops;
        map<Neuron*, unsigned> hops;
        
        //Put inputNeurons to front
        BOOST_FOREACH( Neuron* n, inputNeurons )
        {
            rawFront.push_back(n);
            hops[n] = 1;
        }
        formatFront(rawFront);
        
        //Bias neuron is kind of input neuron
        Neuron* biasNeuron = const_cast<Net*>(this)->findNeuron(biasId);
        cache.data[0][0].push_back(biasNeuron);

        /*
         * Cache looks like this:
         *
         * vector<FrontType> cache.data
         *     |
         *     |-(0) vector<ThreadTaskType>      <-- * front pounsigneder pounsigneds to this vector
         *     |-(1) vector<ThreadTaskType>
         *     |-(...)
         *     |-(number_of_layers) vector<ThreadTaskType>
         *                          |
         *                          |-(0) vector<Neuron*> Target neurons for thread1
         *                          |-(1) vector<Neuron*> Target neurons for thread2
         *
         *  At this pounsigned cache.data(0) is the only record and it contains input neurons
         */

        do {
            /*
             * We have better prepare next front
             * At first iteration, if you remember, vector<unsigned> _raw contains unique inputNeurons indexes
             */
            unsigned nCount = rawFront.size();
            for(unsigned i = 0; i < nCount; ++i)
            {
                //pop_front emulation
                Neuron* currentNeuron = rawFront[0];
                rawFront.erase( rawFront.begin() );

                //ok, we've got cur_neuron. We will iterate through his Out links
                //and push_back their opposite sides to rawFront
                BOOST_FOREACH( Link& link, currentNeuron->links )
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
                     *   T = N, N < C - it is recurrent link. Dont touch T and dont place it unsignedo rawFront
                     *   T = C  - it is stupid recursive topology. Currently unsupported. Raise exception
                     *   T = C, but t=c  - it is recurrent link over 1 neuron. It is supported
                     *   T = C + 1 - T already hadled. Silently ignore T. We can add T to rawFront
                     *   T > C + 1 - impossible. Somebody changed hops by hand and didn't touch cache or
                     *               after last cache generation algorithm didn't set neuron's hops to zero
                     */

                    //Assume that when cache becomes coherent, all neuron[hops] vars become zero
                    if(hops[link.getTo()] == 0)
                        hops[link.getTo()] = hops[currentNeuron] + link.getLatency();

                    if(hops[link.getTo()] == hops[currentNeuron] + 1)
                        rawFront.push_back(link.getTo()); 

                    if(hops[link.getTo()] == hops[currentNeuron] && link.getTo() != currentNeuron)
                        throw Exception::Unbelievable()<<"Net::run(): cur_neuron.hops == to.hops. "
                                                            "There is no support for such topologies yet\n";
                } //BOOST_FOREACH( Link )

            } //rawFront iteration ( Neuron )

            //new rawFront formed
            formatFront(rawFront);
            
        } while( rawFront.size() > 0 );

        //We rebuilded cache
        cache.fixed();

    } //regenerateCache

}; //pann

