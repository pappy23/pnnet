//Net.cpp

#include "Runner.h"
#include "Neuron.h"

#include "Net.h"

using namespace std;
using boost::shared_ptr;

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
    Net::addInputNeuron(shared_ptr<Neuron> _neuron)
    {
        cache.touch();

        inputNeurons.push_back(_neuron);
    } //addInputNeuron

    void
    Net::removeNeuron(shared_ptr<Neuron> _neuron)
    {
        cache.touch();

        //Delete all connections to/from current neuron
        BOOST_FOREACH(const Link& link, _neuron->getInConnections())
            link.getTo()->delOutConnection(_neuron);

        BOOST_FOREACH(const Link& link, _neuron->getOutConnections())
            link.getTo()->delInConnection(_neuron);

        //Remove neuron from registers
        inputNeurons.remove(_neuron);

        Debug()<<_neuron.use_count()<<'\n';
    } //delNeuron

    shared_ptr<Weight>
    Net::addConnection(shared_ptr<Neuron> _from, shared_ptr<Neuron> _to, shared_ptr<Weight> _weight)
    {
        cache.touch();

        if(!_weight)
            _weight.reset(new Weight());

        _from->addOutConnection(_to, _weight);
        _to->addInConnection(_from, _weight);

        return _weight;
    } //addConnection

    void
    Net::delConnection(shared_ptr<Neuron> _from, shared_ptr<Neuron> _to)
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

        typedef shared_ptr<Neuron> NP;

        unsigned i = 0;
        BOOST_FOREACH( NP n, inputNeurons)
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
            _output[i] = cache.layers.back()[i]->getActivationValue();
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
            threadPool.add_thread( new boost::thread(Net::threadBase, &_runner, this, thread, workThreads, &barrier) );
        
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
    Net::formatFront(vector<shared_ptr<Neuron> >& _raw) const
    {
        sort(_raw.begin(), _raw.end());
        vector<shared_ptr<Neuron> >::iterator it = unique(_raw.begin(), _raw.end());
        _raw.resize( it - _raw.begin() );

        if(_raw.size() > 0)
            cache.layers.push_back(_raw);
    } //formatFront

    void
    Net::regenerateCache() const
    {
        cache.flush(); 

        typedef shared_ptr<Neuron> NP;

        //Here we will place neuron's IDs that will become front, with duplicates
        vector<NP> rawFront;

        /*
         * Function operates with "hops" attribute of every Neuron
         * to build adequate cache.
         * Unfortunetly, map<unsigned, Neuron>::iterator doesn't have operator< , so
         * we shold write own comparison class for hops<>. I placed it to Utils.h
         */
        //map<Neuron*, unsigned, NeuronIterCompare> hops;
        map<NP, unsigned> hops;
        
        //Put inputNeurons to front
        BOOST_FOREACH( NP n, inputNeurons )
        {
            rawFront.push_back(n);
            hops[n] = 1;
        }
        formatFront(rawFront);
        
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
                NP currentNeuron = rawFront[0];
                rawFront.erase( rawFront.begin() );

                //ok, we've got cur_neuron. We will iterate through his Out links
                //and push_back their opposite sides to rawFront
                BOOST_FOREACH( const Link& link, currentNeuron->getOutConnections() )
                {
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
                        throw Exception()<<"Net::run(): cur_neuron.hops == to.hops. "
                                        "There is no support for such topologies yet\n";
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
                                                      unsigned _threads,
                                                      boost::barrier* _barrier)
    {
        RunDirection dir = _runner->getDirection();
        const NetCache& _cache = _net->getCache();

        unsigned layer;
        (dir == ForwardRun) ?  (layer = 0) : (layer = _cache.layers.size() - 1);

        do {
            //Process current layer
            for(unsigned i = _cur_thread; i < _cache.layers[layer].size(); i += _threads)
                _runner->run( *_cache.layers[layer][i], *_net ); //We pass Net* to runner, because 
                                                                //learning algorithms require 
                                                                //read-only access to Net attributes

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

