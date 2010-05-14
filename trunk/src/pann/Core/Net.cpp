//Net.cpp

#include <boost/foreach.hpp>

#include "Runner.h"
#include "Neuron.h"

#include "Net.h"

using namespace std;

namespace pann
{
    Net::Net()
    {
        set_work_threads_count(0);
    } //Net

    Net::~Net()
    {
    } //~Net

    void
    Net::add_input_neuron(NeuronPtr neuron)
    {
        cache.touch();

        input_neurons.push_back(neuron);
    } //add_input_neuron

    void
    Net::remove_neuron(NeuronPtr neuron)
    {
        cache.touch();

        //Delete all connections to/from current neuron
        BOOST_FOREACH(const Link& link, neuron->input_links)
            link.get_to()->remove_out_connection(neuron);

        BOOST_FOREACH(const Link& link, neuron->output_links)
            link.get_to()->remove_in_connection(neuron);

        //Remove neuron from registers
        input_neurons.remove(neuron);

        Debug()<<neuron.use_count()<<'\n';
    } //remove_neuron

    WeightPtr
    Net::add_connection(NeuronPtr from, NeuronPtr to, WeightPtr weight)
    {
        cache.touch();

        if(!weight)
            weight.reset(new Weight());

        from->add_out_connection(to, weight);
        to->add_in_connection(from, weight);

        return weight;
    } //add_connection

    void
    Net::remove_connection(NeuronPtr from, NeuronPtr to)
    {
        cache.touch();

        /* Short unsignedroduction:
         * Neuron_from               Neuron_to
         *  Link                      Link
         *    to =>Neuron2              to =>Neuron1
         *    w  =>weight1              w  =>weight1
         *    dir=>out                  dir=>in
         */

        from->remove_out_connection(to);
        to->remove_in_connection(from);
    } //remove_connection

    void
    Net::set_input(const valarray<Float>& input)
    {
        if(input.size() < input_neurons.size())
            throw SizeMismatch()<<"set_input(): Supplied input size is smaller "
                                     "then number of input neurons\n";

        if(input.size() > input_neurons.size())
            Warning()<<"set_input(): Input size is bigger then input neurons count. "
                             "Check getInputMap() output\n";

        unsigned i = 0;
        BOOST_FOREACH( const NeuronPtr& n, input_neurons)
           n->input = input[i++];
    } //set_input

    void
    Net::get_output(valarray<Float>& output) const
    {
        if(!cache.is_ok())
            regenerate_cache();

        vector<NeuronPtr>& last_layer = *(cache.layers.end() - 2);
        unsigned output_size = last_layer.size();

        output.resize(output_size);
        for(unsigned i = 0; i < output_size; ++i)
            output[i] = last_layer[i]->output;
    } //get_output

    void
    Net::run(RunnerPtr runner, RunDirection direction)
    {
        if( !cache.is_ok() )
            regenerate_cache();

        boost::thread_group thread_pool;
        boost::barrier barrier(work_threads_count);

        //We must give parameters by pointer, because boost will copy all arguments to thread
        for(unsigned thread = 0; thread < work_threads_count; ++thread)
            thread_pool.add_thread( new boost::thread(Net::thread_base, direction, runner, this, thread, &barrier) );

        //wait for threads to finish
        thread_pool.join_all();
    } //run

    const NetCache&
    Net::get_cache() const
    {
        if(!cache.is_ok())
            regenerate_cache();

        return cache;
    } //get_cache

    unsigned
    Net::get_work_threads_count() const
    {
        return work_threads_count;
    } //get_work_threads_count

    void Net::set_work_threads_count(unsigned count)
    {
        if(count <= 0)
            work_threads_count = boost::thread::hardware_concurrency();
        else
            work_threads_count = count;

    } //set_work_threads_count

    void
    Net::format_front(list<NeuronPtr>& raw) const
    {
        cache.layers.push_back(vector<NeuronPtr>());

        if(raw.size() > 0)
        {
            raw.sort();
            raw.unique();

            for(list<NeuronPtr>::iterator it = raw.begin(); it != raw.end(); ++it)
                cache.layers.back().push_back(*it);
        }
    } //format_front

    void
    Net::regenerate_cache() const
    {
        //TODO: if user set's latency > 1 for regular links - shit may happen
        //TODO: Latency - is very dangerous tool. It's not difficult to understand, 
        //TODO: why this feature is still not implemented in Neuron/Net interface :)
        cache.flush();

        //Here we will place neuron's IDs that will become front, with duplicates
        list<NeuronPtr> raw_front;

        /*
         * Function operates with "hops" attribute of every Neuron
         * to build adequate cache.
         */
        map<NeuronPtr, unsigned> hops;

        //Put inputNeurons to front
        BOOST_FOREACH( const NeuronPtr& n, input_neurons )
        {
            raw_front.push_back(n);
            hops[n] = 1;
        }
        format_front(raw_front);

        /*
         * Cache looks like this:
         * At this point cache.layers[0] is the only record and it contains input neurons
         */
        do {
            /*
             * We have to prepare next front
             * At first iteration, if you remember, vector<NeuronPtr> rawFront contains unique inputNeurons
             */
            unsigned nCount = raw_front.size();
            Debug()<<nCount<<"\n";
            for(unsigned i = 0; i < nCount; ++i)
            {
                //pop_front emulation
                NeuronPtr current_neuron = raw_front.front();
                raw_front.pop_front();

                //ok, we've got cur_neuron. We will iterate through his Out links
                //and push_back their opposite sides to rawFront
                BOOST_FOREACH( const Link& link, current_neuron->output_links )
                {
                    const NeuronPtr& to_neuron = link.get_to();
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
                    if(hops[to_neuron] == 0)
                        hops[to_neuron] = hops[current_neuron] + link.get_latency();

                    if(hops[to_neuron] == hops[current_neuron] + 1)
                        raw_front.push_back(to_neuron);

                } //BOOST_FOREACH( Link )

            } //rawFront iteration ( Neuron )

            //new rawFront formed
            format_front(raw_front);

        } while( raw_front.size() > 0 );

        //We rebuilded cache
        cache.fixed();

    } //regenerateCache

    void
    Net::thread_base(RunDirection direction, RunnerPtr runner, Net *net, unsigned cur_thread, boost::barrier *barrier)
    {
        const NetCache& cache = net->get_cache();

        unsigned layer;
        (direction == ForwardRun) ?  (layer = 0) : (layer = cache.layers.size() - 1);

        const unsigned threads = net->get_work_threads_count();

        do {
            //Process current layer
            for(unsigned i = cur_thread; i < cache.layers[layer].size(); i += threads)
                runner->run( ObjectConstPtr(net), cache.layers[layer][i]); //We pass Net* to runner, because
                                                                    //learning algorithms require
                                                                    //read-only access to Net attributes

            //Wait for other threads
            barrier->wait();
        } while( (direction == ForwardRun && ++layer < cache.layers.size()) || (direction == BackwardRun && layer-- > 0) );
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
    } //thread_base

}; //pann

