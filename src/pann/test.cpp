
#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

using namespace std;
using namespace boost;

namespace pann
{
    typedef size_t Hash;
    typedef double Float;
    const Float inf = std::numeric_limits<Float>::infinity();

    /**
     * Basic class for all exceptions
     * Use case: throw Exception()<<"Hello"<<','<<" world!"<<5<<'\n')
     *      catch(Exception& e)
     * Don't forget to declare your CoolException, derived from Exception
     */
    class Exception : public std::exception
    {
    public:
        Exception() {};

        Exception(const Exception& _rhs )
        {
            msg = _rhs.msg;
        }

        virtual ~Exception() throw() {};

        virtual const char * what() const throw()
        {
            return msg.c_str();
        }

        template<typename T>
        Exception& operator<<(const T& _arg)
        {
            std::stringstream ss;
            ss << _arg;
            accumulate(ss.str());

            return *this;
        }

    protected:
        virtual void accumulate(const std::string& _arg)
        {
            msg += _arg;
        }

    private:
        std::string msg;
    }; //Exception

    class Info : public Exception
    {
    protected:
        virtual void accumulate(const std::string& _arg)
        {
            std::cout<<_arg;
        }
    }; //Info

    /// Debug
    class Debug : public Info {};

    /// Reference to unexistent object was requested
    class NotFound : public Exception {};

    /// Count of elements mismatch
    class SizeMismatch : public Exception {};

    /// Exceptionfor raising on filesystem failures (missing file etc.)
    class IoError : public Exception {};

    /**
     * All activation functions inherit Tf
     */
    struct Tf
    {
        virtual Float fx(Float x) = 0;
        virtual Float df_dy(Float y) = 0;
    }; //Tf
    typedef shared_ptr<Tf> TfPtr;
    typedef shared_ptr<const Tf> TfConstPtr;

    struct Object
    {
        map<Hash, Float> attribute_map;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(attribute_map);
            };
    }; //Object
    typedef shared_ptr<Object> ObjectPtr;
    typedef shared_ptr<const Object> ObjectConstPtr;

    /**
     * Weight object, used in pann::Link. Weight might be shared among different Links.
     * Link contains WeightPtr for this object
     */
    struct Weight : Object
    {
        explicit Weight(Float initial_value) :
            value(initial_value), usage_count(0) {};
        virtual ~Weight() {}

        Float value;
        int usage_count; ///< Used by weight update algorithms for shared weights
        mutex thread_guard;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
               & BOOST_SERIALIZATION_NVP(value)
               & BOOST_SERIALIZATION_NVP(usage_count);
        };
    }; //Weight
    typedef shared_ptr<Weight> WeightPtr;
    typedef shared_ptr<const Weight> WeightConstPtr;


    struct Neuron;
    typedef shared_ptr<Neuron> NeuronPtr;
    typedef shared_ptr<const Neuron> NeuronConstPtr;

    /**
     * Link between two neurons
     */
    struct Link : Object
    {
        Link(NeuronPtr to, WeightPtr weight, unsigned const latency = 1)
            : to(to), weight(weight), latency(latency) {};
        virtual ~Link() {};

        NeuronPtr to;
        WeightPtr weight; /// Pointer to Weight object (might be shared between different links)
        int latency;

    private:
        /**
         * Link is not assign-copyable
         */
        Link& operator=(const Link& _rhs)
        {
            /*
            Info()<<"Link::operator=()\n";
            to = _rhs.to;
            weight = _rhs.weight;
            latency = _rhs.latency;
            */
            return *this;
        };

    private:
        /**
         * Default constructor for serialization
         * Of course we can use save_construct_data/load_construct_data, but
         * default constructor is much simpler
         */
        Link() { };

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(to)
                 & BOOST_SERIALIZATION_NVP(latency)
                 & BOOST_SERIALIZATION_NVP(weight);
            };
    }; //Link

    struct Runner;
    typedef shared_ptr<Runner> RunnerPtr;
    typedef shared_ptr<const Runner> RunnerConstPtr;

    struct Neuron : Object
    {
        Float bias;
        Float input;
        Float output;

        vector<Link> input_links, output_links;

        RunnerPtr fire;
        RunnerPtr learn;
        TfPtr tf;

    private:
        //friend template<class Archive> void Net::serialize(Archive & ar, const unsigned int version);
        //friend class Net;

        Neuron() {};

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 //@see Net::serialize()
                 //& BOOST_SERIALIZATION_NVP(links_out)
                 //& BOOST_SERIALIZATION_NVP(links_in)
                 & BOOST_SERIALIZATION_NVP(input)
                 & BOOST_SERIALIZATION_NVP(output)
                 & BOOST_SERIALIZATION_NVP(bias)
                 & BOOST_SERIALIZATION_NVP(tf)
                 & BOOST_SERIALIZATION_NVP(fire)
                 & BOOST_SERIALIZATION_NVP(learn);
            };
    }; //Neuron
    typedef shared_ptr<Neuron> NeuronPtr;
    typedef shared_ptr<const Neuron> NeuronConstPtr;

    /**
     * Abstract cache object
     * In reality every class should inherit own SuperDuperCache from this class
     */
    struct Cache
    {
        Cache() : coherent(false) {};
        virtual ~Cache();

        bool coherent;

        virtual void flush() = 0;

        void touch()
        {
            coherent = false;
        };

        void fixed()
        {
            coherent = true;
        };

        bool is_ok() const
        {
            return coherent;
        };

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_NVP(coherent);
        };
    }; //Cache

    struct NetCache : Cache
    {
        NetCache() {};
        virtual ~NetCache() {};

        typedef vector<NeuronPtr> Front;

        //TODO: Should we hide internal details from user?
        //Solutions:
        //1)Write restricted interface to layers
        //2)Derive NetCache from Cache AND vector<FrontType>
        //3)write const vector<const FrontType> NetCache::layers() - current solution
        vector<Front> layers;

        virtual void flush()
        {
            layers.clear();
            touch();
        };

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Cache)
                   & BOOST_SERIALIZATION_NVP(layers);
            };
    }; //NetCache

    struct Net : Object
    {
        enum RunDirection { ForwardRun, BackwardRun };

        /**
         * Default constructor
         * Creates empty net and sets threadCount to
         * hardware specific number (depends on available processors)
         */
        Net()
        {
            set_work_threads_count(0)
        };

        virtual ~Net() {};

        /**
         * Manipulate neurons in network
         */
        void add_input_neuron(NeuronPtr neuron)
        {
            cache.touch();

            input_neurons.push_back(neuron);
        };

        //TODO Fix removal of neurons and connections.
        //We can stuck with hanging part of topology
        void remove_neuron(NeuronPtr neuron)
        {
            cache.touch();

            //Delete all connections to/from current neuron
            BOOST_FOREACH(const Link& link, neuron->input_links)
                link.getTo()->delOutConnection(neuron);

            BOOST_FOREACH(const Link& link, _neuron->output_links)
                link.getTo()->delInConnection(_neuron);

            //Remove neuron from registers
            inputNeurons.remove(_neuron);

            Debug()<<_neuron.use_count()<<'\n';
        };

        /**
         * Manage connections between neurons
         * TODO: add connections with different latencies (shortcut links)
         */
        WeightPtr add_connection(
                NeuronPtr from,
                NeuronPtr to,
                WeightPtr weight = WeightPtr((Weight*)0))
        {
        };

        void remove_connection(NeuronPtr from, NeuronPtr to)
        {
        };

        /**
         * Add values to input neurons receptive fields
         */
        void set_input(const valarray<Float>& input)
        {
        };

        /**
         * Assign neurons outputs to specified by @param _output valarray
         * (it is slower then above version, but more useful)
         */
        void get_output(valarray<Float>& output) const
        {
        };

        /**
         * Apply @param _runner Runner to each neuron,
         * layer by layer
         * Note: layers are computed automaticaly and stored in cache
         * See regenerateCache() implementation for more details
         */
        void run(RunDirection direction, RunnerPtr runner)
        {
        };

        /**
         * Public interface to private attributes
         * (they are used while training or painting net in pann_viewer)
         */
        const NetCache& get_cache() const
        {
        };

        /**
         * Manipulate count of work threads
         */
        unsigned get_work_threads_count() const
        {
        };

        void set_work_threads_count(unsigned count)
        {
        };

    private:
        list<NeuronPtr> input_neurons;
        NetCache mutable cache;
        unsigned work_threads_count;

        /**
         * Helper used by regenerateCache()
         */
        void format_front(list<NeuronPtr>& raw) const
        {
        };

        /**
         * This function updates cache
         * Be extremely careful!
         */
        void regenerate_cache() const
        {
        };

        /**
         * This function is executed by work thread, instantiated from run()
         * @param _runner Runner to apply
         * @param _net Net context, used for access to global net attributes
         * @param _cur_thread Current work thread number
         * @param _barrier See implementation
         */
        static void thread_base(RunDirection direction, RunnerPtr runner, ObjectPtr net, unsigned cur_thread, boost::barrier *barrier)
        {
        };

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                using namespace boost::serialization;

                //It's for manual serialization of Neuron connections
                if(typename Archive::is_saving() && !cache.is_ok())
                    regenerate_cache();

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(cache)
                 & BOOST_SERIALIZATION_NVP(input_neurons)
                 & BOOST_SERIALIZATION_NVP(work_threads_count);

                //Serialize Neuron connections
                for(unsigned i = 0; i < cache.layers.size(); ++i)
                    for(unsigned j = 0; j < cache.layers[i].size(); ++j)
                    {
                        ar & make_nvp("input_links", cache.layers[i][j]->input_links);
                        ar & make_nvp("output_links", cache.layers[i][j]->output_links);
                    }
            };
    }; //Net

    struct Runner
    {
        virtual void operator() (ObjectPtr, NeuronPtr) = 0;
    }; //Runner
    typedef shared_ptr<Runner> RunnerPtr;
    typedef shared_ptr<const Runner> RunnerConstPtr;

    //Tools
    void link_neurons(NeuronPtr n1, NeuronPtr n2, WeightPtr *weight)
    {
    }; //link_neurons

    Hash hash(const char* name)
    {
        static boost::hash<std::string> hasher;
        return hasher(name);
    }; //hash

    /**
     * Very cool pseudorandom number generator
     * Returns good random number in [0.0; 1.0] range
     * Uses boost::random
     */
    Float rand01()
    {
        static boost::lagged_fibonacci44497 engine;
        static boost::uniform_real<Float> distribution(0, 1);
        static boost::variate_generator<
            boost::lagged_fibonacci44497,
            boost::uniform_real<Float>
        > generator(engine, distribution);

        return generator();
    }; //rand01

    /**
     * Uses rand01(), but scales it to range [_min; _max]
     */
    Float rand(Float _min, Float _max)
    {
        //Generate v from (0; 1) and squash it to (_min; _max) range
        Float v = rand01();
        Float a = ( _max - _min );
        Float b = _max - a;
        v = a * v + b;

        return v;
    }; //rand

    /**
     * Drop coin with specified probability
     */
    bool rand_coin(Float _probability = 0.5)
    {
        return rand01() < _probability;
    } //rand_coin

}; //pann
