//Net.cpp

#include "Net.h"

using std::pair;
using std::map;
using std::list;
using std::vector;
using boost::any_cast;

namespace pann
{
    Net::Net()
    {
        lastNeuronId = 0;
        threadCount = 1;
    } //Net

    Net::Net(int _threads)
    {
        Net::Net();
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

        if(_threads < 1 || _threads > 5)
            throw Exception::RangeMismatch()<<"Net::run(): currently only up to 5 concurrent threads supported\n";

        threadCount = _threads;
    } //setThreadCount

    Net::NeuronIter Net::findNeuron(int _neuronId)
    {
        NeuronIter iter = neurons.find(_neuronId);
        if(neurons.end() == iter)
            throw Exception::ObjectNotFound()<<"findNeuron(): Neuron "<<_neuronId<<" not found\n";
        
        return iter;
    } //isNeuronExist

    void Net::formatFront(vector<int>& _raw)
    {
        cache.data.push_back( NetCache::FrontType() );
        NetCache::FrontType& tasks = cache.data[cache.data.size() - 1];
        
        for(int i = 0; i < threadCount; i++)
            tasks.push_back( vector<Neuron*>() );

        vector<int>::iterator it = unique(_raw.begin(), _raw.end());
        _raw.resize( it - _raw.begin() );

        for(int i = 0; i < _raw.size(); ++i)
        {
            Neuron& n = neurons[ _raw[i] ];
            tasks[n.getOwnerThread() % threadCount].push_back(&n);
        }

    } //formatFront

    int Net::addNeuron(ActivationFunction::Base& _activationFunction)
    {
        cache.touch();

        if(!neurons.insert( pair<int, Neuron>(++lastNeuronId, Neuron(_activationFunction)) ).second)
            throw Exception::ElementExists()<<"Net::addNeuron(): insertion of neuron "<<lastNeuronId<<" failed\n";
        
        return lastNeuronId;
    } //addNeuron

    int Net::addInputNeuron()
    {
        int neuronId = addNeuron(ActivationFunction::Linear::Instance());
        setNeuronRole(neuronId, Net::InputNeuron);

        return neuronId;
    } //addInputNeuron

    int Net::addOutputNeuron(ActivationFunction::Base& _activationFunction)
    {
        int neuronId = addNeuron(_activationFunction);
        setNeuronRole(neuronId, Net::OutputNeuron);

        return neuronId;
    } //addOutputNeuron

    void Net::delNeuron(int _neuronId)
    {
        cache.touch();

        if( !neurons.erase(_neuronId) )
            throw Exception::ObjectNotFound()<<"Net::delNeuron(): neuron "<<_neuronId<<" not found\n";
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

    void Net::addConnection(int _from, int _to, float _weightValue)
    {
        cache.touch();

        Neuron& from = findNeuron(_from)->second;
        Neuron& to = findNeuron(_to)->second;

        from.connect(to, _weightValue);
    } //addConnection

    void Net::delConnection(int _from, int _to)
    {
        cache.touch();

        Neuron& from = findNeuron(_from)->second;
        Neuron& to = findNeuron(_to)->second;

        from.disconnect(to);        
    } //delConnection

    std::vector<int> Net::getInputMap()
    {
        vector<int> result;

        list< NeuronIter >::iterator iter = inputNeurons.begin();
        for(; iter != inputNeurons.end(); ++iter)
            result.push_back((*iter)->first);

        return result;
    } //getInputMap

    std::vector<int> Net::getOutputMap()
    {
        vector<int> result;

        list< NeuronIter >::iterator iter = outputNeurons.begin();
        for(; iter != outputNeurons.end(); ++iter)
            result.push_back((*iter)->first);

        return result;
    } //getOutputMap

    void Net::setInput(vector<float> _input)
    {
        if(_input.size() < inputNeurons.size())
            throw Exception::SizeMismatch()<<"setInput(): Supplied input size is smaller then number of input neurons\n";

        if(_input.size() > inputNeurons.size())
            Exception::Warning()<<"setInput(): Input size is bigger then input neurons count. Check getInputMap() output\n";

        list< NeuronIter >::iterator it = inputNeurons.begin();
        for(int i = 0; it != inputNeurons.end(); ++it, ++i)
        {
            (*it)->second.receptiveField = _input[i];
        }
    } //setInput

    vector<float> Net::getOutput()
    {
        vector<float> result;
        list< NeuronIter >::iterator it = outputNeurons.begin();
        for(; it != outputNeurons.end(); ++it)
            result.push_back((*it)->second.activationValue);

        return result;
    } //setInput

    /*
     * This function updates cache and does
     * forward propagation through neural network
     * Be extremely careful!
     */
    void Net::run()
    {
        vector<int> rawFront; //Here we will place neuron's ids that will become front, with duplicates
        //If cache is not up2date, flush it and fill again
        if( !cache.isOk() )
        {
            cache.flush();
            
            //Put inputNeurons to front
            BOOST_FOREACH( NeuronIter iter, inputNeurons )
            {
                rawFront.push_back(iter->first); 
                iter->second.a_hops = (int)1;
            }

            formatFront(rawFront);
        }

        /*
         * Cache looks like that:
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
        while(rawFront.size() > 0)
        {
            NetCache::FrontType* front = &cache.data[layer++];

            //front is ready, lets start our pretty threads =)
            for(int i = 0; i < threadCount; i++)
            {
                //TODO: threading
                //runFeedForwardThread( (*front)[i] );
            }
            
            if( !cache.isOk() )
            {
                /*
                 * We have better prepare next front
                 * This block is done one time per cache generation and it
                 * is executed by main() thread
                 *
                 * At first iteration, if you remember, vector<int> _raw contains unique inputNeurons indexes
                 */
                int nCount = rawFront.size();
                for(int i = 0; i < nCount; ++i)
                {
                    //pop_front emulation
                    int cur_neuronId = rawFront[0];
                    rawFront.erase( rawFront.begin() );
                    Neuron& cur_neuron = neurons[cur_neuronId];

                    //ok, we've got cur_neuron. We will iterate through his Out links 
                    //and push_back their opposite sides to rawFront
                    BOOST_FOREACH( Link& link, cur_neuron.links )
                    {
                        //Only feedforward links
                        if(link.direction == Link::In)
                            continue;

                        //Assume that when cache becomes coherent, all neuron.hops vars become zero
                        if(link.to.hops == 0)
                        {
                            link.to.hops = cur_neuron.hops + 1;
                            //find cur_neuron, get it's id and push_back it to rawFront
                            //rawFront.push_back();
                        }

                        if(link.to.hops == cur_neuron.hops)
                            throw Exception::Unbelievable()<<"Net::run(): cur_neuron.hops == to.hops. "
                                                                "There is no support for such topologies yet\n";
                        if( link.to.hops > ( cur_neuron.hops + 1 ) )
                            throw Exception::Unbelievable()<<"Net::run(): cache regeneration "
                                                            "discovered that hops was not set to zero\n";
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
                    } //BOOST_FOREACH

                } //link iteration

                //new rawFront formed
                formatFront(rawFront);

            } // if( !cache.isOk() )

            //wait for threads to finish
            //TODO: wait for work threads to finish
            
            ////set hops to zero
        } //while

        //We rebuilded cache
        if( !cache.isOk() )
        {
            cache.fixed();
            //Turn all neurons hops to zero. We may use threads for this
            //TODO^^^
        }

    } //run
/*
    Neuron& Net::getNeuron(int _neuronId)
    {
        NeuronIter i = neurons.find(_neuronId);
        if(i == neurons.end())
            throw Exception::ObjectNotFound()<<"Net::getNeuron(): neuron "<< _neuronId<<"not found\n";

        return i->second;
    } //getNeuron
*/

}; //pann

