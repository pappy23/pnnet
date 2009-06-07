//Net.cpp

#include "Runner.h"
#include "Neuron.h"

#include "Net.h"

using namespace std;

namespace pann
{
    Net::Net()
    {
        setWorkThreadsCount(0);
    } //Net

    Net::~Net()
    {
    } //~Net

    void
    Net::addInputNeuron(NeuronPtr _neuron)
    {
        cache.touch();

        inputNeurons.push_back(_neuron);
    } //addInputNeuron

    void
    Net::removeNeuron(NeuronPtr _neuron)
    {
        cache.touch();

        //Delete all connections to/from current neuron
        BOOST_FOREACH(const Link& link, _neuron->links_in)
            link.getTo()->delOutConnection(_neuron);

        BOOST_FOREACH(const Link& link, _neuron->links_out)
            link.getTo()->delInConnection(_neuron);

        //Remove neuron from registers
        inputNeurons.remove(_neuron);

        Debug()<<_neuron.use_count()<<'\n';
    } //delNeuron

    WeightPtr
    Net::addConnection(NeuronPtr _from, NeuronPtr _to, WeightPtr _weight)
    {
        cache.touch();

        if(!_weight)
            _weight.reset(new Weight());

        _from->addOutConnection(_to, _weight);
        _to->addInConnection(_from, _weight);

        return _weight;
    } //addConnection

    void
    Net::delConnection(NeuronPtr _from, NeuronPtr _to)
    {
        cache.touch();

        /* Short unsignedroduction:
         * Neuron_from               Neuron_to
         *  Link                      Link
         *    to =>Neuron2              to =>Neuron1
         *    w  =>weight1              w  =>weight1
         *    dir=>out                  dir=>in
         */

        _from->delOutConnection(_to);
        _to->delInConnection(_from);
    } //delConnection

    void
    Net::setInput(const valarray<Float>& _input)
    {
        if(_input.size() < inputNeurons.size())
            throw SizeMismatch()<<"setInput(): Supplied input size is smaller "
                                     "then number of input neurons\n";

        if(_input.size() > inputNeurons.size())
            Warning()<<"setInput(): Input size is bigger then input neurons count. "
                             "Check getInputMap() output\n";

        unsigned i = 0;
        BOOST_FOREACH( const NeuronPtr& n, inputNeurons)
           n->setInput(_input[i++]);
    } //setInput

    void
    Net::getOutput(valarray<Float>& _output) const
    {
        if(!cache.isOk())
            regenerateCache();

        unsigned output_size = cache.layers.back().size();
        _output.resize(output_size);

        for(unsigned i = 0; i < output_size; ++i)
            _output[i] = cache.layers.back()[i]->getOutput();
    } //getOutput

    void
    Net::run(Runner& _runner)
    {
        if( !cache.isOk() )
            regenerateCache();

        boost::thread_group threadPool;
        boost::barrier barrier(workThreads);

        //We must give parameters by pointer, because boost will copy all arguments to thread
        for(unsigned thread = 0; thread < workThreads; ++thread)
            threadPool.add_thread( new boost::thread(Net::threadBase, &_runner, this, thread, &barrier) );

        //wait for threads to finish
        threadPool.join_all();
    } //run

    const NetCache&
    Net::getCache() const
    {
        if(!cache.isOk())
            regenerateCache();

        return cache;
    } //getCache

    unsigned 
    Net::getWorkThreadsCount() const
    {
        return workThreads;
    } //getWorkThreadsCount

    void Net::setWorkThreadsCount(unsigned _count)
    {
        if(_count <= 0)
            workThreads = boost::thread::hardware_concurrency();
        else
            workThreads = _count;

    } //setWorkThreadsCount

    void
    Net::formatFront(list<NeuronPtr>& _raw) const
    {
        _raw.sort();
        _raw.unique();

        if(_raw.size() > 0)
        {
            cache.layers.push_back(vector<NeuronPtr>());
            for(list<NeuronPtr>::iterator it = _raw.begin(); it != _raw.end(); ++it)
                cache.layers.back().push_back(*it);
        }
    } //formatFront

    void
    Net::regenerateCache() const
    {
        //TODO: if user set's latency > 1 for regular links - shit may happen
        //TODO: Latency - is very dangerous tool. It's not difficult to understand, 
        //TODO: why this feature is still not implemented in Neuron/Net interface :)
        cache.flush();

        //Here we will place neuron's IDs that will become front, with duplicates
        list<NeuronPtr> rawFront;

        /*
         * Function operates with "hops" attribute of every Neuron
         * to build adequate cache.
         */
        map<NeuronPtr, unsigned> hops;

        //Put inputNeurons to front
        BOOST_FOREACH( const NeuronPtr& n, inputNeurons )
        {
            rawFront.push_back(n);
            hops[n] = 1;
        }
        formatFront(rawFront);

        /*
         * Cache looks like this:
         * At this point cache.layers[0] is the only record and it contains input neurons
         */
        do {
            /*
             * We have to prepare next front
             * At first iteration, if you remember, vector<NeuronPtr> rawFront contains unique inputNeurons
             */
            unsigned nCount = rawFront.size();
            for(unsigned i = 0; i < nCount; ++i)
            {
                //pop_front emulation
                NeuronPtr currentNeuron = rawFront.front();
                rawFront.pop_front();

                //ok, we've got cur_neuron. We will iterate through his Out links
                //and push_back their opposite sides to rawFront
                BOOST_FOREACH( const Link& link, currentNeuron->links_out )
                {
                    const NeuronPtr& toNeuron = link.getTo(); 
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
                     *   T = N, N < C - it is recurrent link. Don't touch T and don't place it to rawFront
                     *   T = C  - it is recursive topology(recursion in same layer)
                     *   T = C, but t=c  - it is recurrent link over 1 neuron
                     *   T = C + 1 - T already handled. We should add T to rawFront
                     *   T > C + 1 - latency to T is > 1. Don't touch T.
                     */

                    //Assume that when cache becomes coherent, all neuron[hops] vars become zero
                    if(hops[toNeuron] == 0)
                        hops[toNeuron] = hops[currentNeuron] + link.getLatency();

                    if(hops[toNeuron] == hops[currentNeuron] + 1)
                        rawFront.push_back(toNeuron); 

                } //BOOST_FOREACH( Link )

            } //rawFront iteration ( Neuron )

            //new rawFront formed
            formatFront(rawFront);

        } while( rawFront.size() > 0 );

        //We rebuilded cache
        cache.fixed();

    } //regenerateCache

    void
    Net::threadBase(Runner* _runner, const Net* _net, unsigned _cur_thread, 
                                                      boost::barrier* _barrier)
    {
        RunDirection dir = _runner->getDirection();
        const NetCache& _cache = _net->getCache();

        unsigned layer;
        (dir == ForwardRun) ?  (layer = 0) : (layer = _cache.layers.size() - 1);

        const unsigned threads = _net->getWorkThreadsCount();

        do {
            //Process current layer
            for(unsigned i = _cur_thread; i < _cache.layers[layer].size(); i += threads)
                _runner->run( *_cache.layers[layer][i], *_net ); //We pass Net* to runner, because 
                                                                //learning algorithms require 
                                                                //read-only access to Net attributes

            std::cout<<_cur_thread<<std::endl;
            //Wait for other threads
            _barrier->wait();
        } while( (dir == ForwardRun && ++layer < _cache.layers.size()) || (dir == BackwardRun && layer-- > 0) );
        /*
         * A little comment.
         * Cache structure:
         * Layer1:   thread1_data, thread2_data, ...
         * Layer2:   thread1_data, thread2_data, ...
         * ...
         * LayerN-1: thread1_data, thread2_data, ...
         * LayerN:          <= last layer. ALWAYS empty! (see Net::regenerateCache())
         * cache.size() == N+1;
         * thread_data is vector of Neuron*
         */
    } //threadBase

}; //pann

