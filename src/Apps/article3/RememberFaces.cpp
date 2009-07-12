
#include "pann.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;
using namespace pann::ConvolutionalNetworkTypes;

#define EXP 3
#define EXPERIMENT experiment3

struct ImageWithMetadata
{
    unsigned man; // 1 - 40
    unsigned pose; // 1 - 10
    unsigned shift; // 1 - 4
    unsigned noise; //0 - no noise, 1 -  small noise
    //FIXME Use share_ptr
    Image *img; //Pointer, becase Image lacks default constructor
};

//ORL-faces database
//@see main()
vector<ImageWithMetadata> orl;

/**
 * Converts orl image to TrainPattern
 * @param _men - number of outputs
 */
TrainPattern imgm2tp(const ImageWithMetadata& _data, unsigned _men)
{
    //Convert image to TrainPattern
    TrainPattern tp(95*95, _men);
    tp.input() = _data.img->getAverageValarray();
    squash(tp.input(), 0.0, 255.0, -1.8, +1.8);
    for(unsigned j = 0; j < _men; ++j)
        tp.desired_output()[j] = -1.8;
    tp.desired_output()[_data.man - 1] = +1.8;

    return tp;
} //imgm2tp

/**
 * Build Mirror Convolutional Network topology
 * @see ConvolutionalNetwork()
 */
#if EXP==1
NetPtr
MirrorConvolutionalNetwork(vector<unsigned> _layers,
    Float _connection_density = 0.8,
    unsigned _window_width = 5,
    unsigned _window_height = 5,
    unsigned _window_horiz_overlap = 3,
    unsigned _window_vert_overlap = 3,
    ActivationFunctionPtr _input_af  = TanH::Instance(),
    ActivationFunctionPtr _conv_af   = TanH::Instance(),
    ActivationFunctionPtr _ss_af     = TanH::Instance(),
    ActivationFunctionPtr _output_af = Linear::Instance()
    )
{
    Model netm_left = ConvolutionalNetworkModel(
            _layers,
            _connection_density,
            _window_width,
            _window_height,
            _window_horiz_overlap,
            _window_vert_overlap,
            _input_af,
            _conv_af,
            _ss_af,
            _output_af);

    Model netm_right = ConvolutionalNetworkModel(
            _layers,
            _connection_density,
            _window_width,
            _window_height,
            _window_horiz_overlap,
            _window_vert_overlap,
            _input_af,
            _conv_af,
            _ss_af,
            _output_af);

    NetPtr net(new Net());

    unsigned last_layer = netm_left.size() - 1;

    //Fix wrong link directions in netm_right
    for(unsigned layer = 0; layer < netm_right.size(); ++layer)
    {
        for(unsigned plane = 0; plane < netm_right[layer].size(); ++plane)
        {
            for(unsigned i = 0; i < netm_right[layer][plane].size(); ++i)
            {
                for(unsigned j = 0; j < netm_right[layer][plane][i].size(); ++j)
                {
                    NeuronPtr n = netm_right[layer][plane][i][j];
                    list<Link>& in_conn = const_cast<list<Link>& >(n->getInConnections()); 
                    list<Link>& out_conn = const_cast<list<Link>& >(n->getOutConnections()); 
                    swap(in_conn, out_conn);
                    n->get<OpenGlAttributes>().x = (signed int)((last_layer + 2) * 1000.0 - n->get<OpenGlAttributes>().x);
                }
            }
        }
    }

    //Gluing two parts together
    for(unsigned i = 0; i < netm_left[last_layer].size(); ++i)
        net->addConnection(netm_left[last_layer][i][0][0], netm_right[last_layer][i][0][0]);

    //Creating Net from model
    for(unsigned i = 0; i < netm_left[0][0].size(); ++i)
        for(unsigned j = 0; j < netm_left[0][0][0].size(); ++j)
            net->addInputNeuron(netm_left[0][0][i][j]);

    return net;
} //MirrorConvolutionalNetwork
#endif

/**
 * Copy ORL database to memory
 */
void
readImages(const char* _listfile, vector<ImageWithMetadata>& _data)
{
    _data.clear();

    ifstream in(_listfile);
    if(!in)
        throw IoError()<<"Can't read supplied list\n";

    while(!in.eof())
    {
        ImageWithMetadata tmp;
        string fname;
        in >> fname >> tmp.man >> tmp.pose >> tmp.shift >> tmp.noise;

        bool error = false;
        try {
            tmp.img = new Image(ImageIo::readImage(fname));
        } catch(Exception&) {
            error = true;
        }

        if(!error)
            _data.push_back(tmp);
    }

    cout<<"Read "<<_data.size()<<" images\n";
} //readImages

/**
 * Test1.
 * постановка эксперимента:
 * 1)строим сверточную сеть с конфигурацией
 * 95x95
 * 46x46 46x46
 * 23x23 23x23
 * 10x10 10x10
 * 5x5 5x5
 * 1x1 1x1
 *
 * 2)строим вторую такую же сеть
 * 3) соединяем выходные нейроны обоих сетей
 *
 * N1 --> N1'
 * N2 --> N2'
 * Т.е. не каждый с каждым
 *
 * 4)загружаем картинки 1 человека (10 ракурсов, вариант с малым шумом и без
 * шума. Каждый ракурс - по 4 варианта)
 * 5)выбираем из всех фоток одну без шума, в анфас. Это будет эталон
 * 6)учим сеть, показывая фотки на входе и требуя на выходе эталон
 * 7)из фоток отбирается 20% на тесты
 * 8)строим график ошибки для множества обучения и множества тестового
 * 9)делаем выводы
 *
 * Вариант 2:
 * Учим не на эталоне, а на куче комбинаций
 */
#if EXP==1
void experiment1()
{
    Info()<<"Constructing mirror net [10 50 250]...\n";
    vector<unsigned> planes;
    planes += 1,1,1;
    NetPtr pnet = MirrorConvolutionalNetwork(planes, 0.8);

    //Select only faces of first man
    Info()<<"Filtering faces... ";
    vector<ImageWithMetadata> raw_data;
    for(unsigned i = 0; i < orl.size(); ++i)
        if(1 == orl[i].man)
            raw_data.push_back(orl[i]);
    Info()<<raw_data.size()<<" images\n";

    //Choosing picture to train against
    ImageWithMetadata template_img;
    do {
        template_img = raw_data[std::rand() % raw_data.size()];
    } while(template_img.noise > 0);
    ImageIo::writeImage(*(template_img.img), "TemplateImage.pgm", ImageIo::PGM);
    cout<<"Training against template image. It's saved as TemplateImage.pgm\n";

    //Formatting TrainData from raw_data
    TrainData tdata;
    for(unsigned i = 0; i < raw_data.size(); ++i)
    {
        TrainPattern tp(95*95, 95*95);
        tp.input() = raw_data[i].img->getAverageValarray();
        squash(tp.input(), 0.0, 255.0, -1.8, +1.8);
        tp.desired_output() = template_img.img->getAverageValarray();
        squash(tp.desired_output(), 0.0, 255.0, -1.8, +1.8);
        tdata.push_back(tp);
    }

    //Test run
    cout<<"Test run\n";
    pnet->setInput(tdata[0].input());
    pnet->run(FeedforwardPropagationRunner::Instance());
    valarray<Float> test_output(95*95);
    pnet->getOutput(test_output);
    squash(test_output, -1.8, +1.8, 0.0, 255.0);
    Image test_run_out(95, 95, test_output);
    ImageIo::writeImage(test_run_out, "TestRunOut.pgm", ImageIo::PGM);
    cout<<"Wrote test run output image to TestRunOut.pgm\n";

    //Trainig net
    pnet->get<LmsNetAttributes>().learningRate = 0.2;
    pnet->get<LmsNetAttributes>().annealingTSC = 3000;
    pnet->get<WeightRandomizationAttributes>().min = -0.6;
    pnet->get<WeightRandomizationAttributes>().max = +0.6;
    //net->run(RandomizeWeightsGaussRunner::Instance());
    pnet->run(RandomizeWeightsAccordingToInputsCountRunner::Instance());
    pnet->setWorkThreadsCount(4);

    //Debug
    //const NetCache& cache = pnet->getCache();
    //for(unsigned i = 0; i < cache.layers.size(); ++i)
    //{
    //    cout<<cache.layers[i].size()<<endl;
    //}

    unsigned const epochs = 1000;
    cout<<"Training for "<<epochs<<" epochs\n";
    for(unsigned i = 1; i < epochs; ++i)
    {
        shuffle(tdata);
        Lms::train(pnet, tdata);
        cout<<i<<"\t"<<ErrorFunction::mse(tdata)<<"\n";
    }

    Storage::save<Storage::txt_out>(pnet, "MirrorConvNet_Exp1.net");
} //experiment1
#endif

/*
 * Строим сверточную сеть которая запоминает одного человека
 * И только его
 */
#if EXP==2
void experiment2()
{
    vector<unsigned> planes;
    planes += 20,50,2;
    NetPtr pnet = ConvolutionalNetwork(planes, 0.8);

    //Formatting TrainData from raw_data
    TrainData tdata;
    for(unsigned i = 0; i < orl.size(); ++i)
    {
        //Only 3 men at this time
        //if(orl[i].man > 3 || orl[i].pose != 1)
        //    continue;

        TrainPattern tp(95*95, 2);
        tp.input() = orl[i].img->getAverageValarray();
        squash(tp.input(), 0.0, 255.0, -1.8, +1.8);
        if(1 == orl[i].man)
        {
            tp.desired_output()[0] = 1.8;
            tp.desired_output()[1] = -1.8;
        } else {
            tp.desired_output()[0] = -1.8;
            tp.desired_output()[1] = 1.8;
        }
        tdata.push_back(tp);
    }

    //Trainig net
    pnet->get<LmsNetAttributes>().learningRate = 0.3;
    pnet->get<LmsNetAttributes>().annealingTSC = 10000;
    pnet->get<WeightRandomizationAttributes>().min = -0.1;
    pnet->get<WeightRandomizationAttributes>().max = +0.1;
    pnet->run(RandomizeWeightsGaussRunner::Instance());
    pnet->setWorkThreadsCount(0);

    unsigned const epochs = 100;
    cout<<"Training for "<<epochs<<" epochs\n";
    for(unsigned i = 1; i < epochs; ++i)
    {
        shuffle(tdata);
        Lms::train(pnet, tdata);
        cout<<i<<"\t"<<ErrorFunction::mse(tdata)<<"\n";
    }

    Storage::save<Storage::txt_out>(pnet, "Exp2.net");
} //experiment2
#endif

/*
 * Большая сверточная сеть, по 1 выходному нейрону на человека
 * Отделяем тестовое множество и учим сеть
 */
#if EXP==3
void experiment3()
{
    unsigned men = 2;
    unsigned epochs = 10;
    vector<unsigned> planes;
    NetPtr pnet;

    //Redefine from file
    map<string, float> params;
    std::ifstream inp("settings.txt");
    if(inp)
    {
        char name[50];
        Float val;

        int buf_size;
        buf_size = sizeof(name);

        while (!inp.eof())
        {
            inp.getline(name,buf_size,'=');
            inp>>val;
            params[name]=val;
            inp.ignore();
        }

        men = params["men"];
        epochs = params["epochs"];
        planes += params["l1"],params["l2"],params["l3"];
        pnet = ConvolutionalNetwork(planes, params["density"]);

        pnet->get<LmsNetAttributes>().learningRate = params["rate"];
        pnet->get<LmsNetAttributes>().annealingTSC = params["tsc"];
    }
    else
    {
        planes += 10,20,30;
        pnet = ConvolutionalNetwork(planes, 1.0);
        pnet->get<LmsNetAttributes>().learningRate = 0.2;
        pnet->get<LmsNetAttributes>().annealingTSC = 20;
    }

    Debug()<<"men="<<men<<"\n"
           <<"epochs="<<epochs<<"\n"
           <<"rate="<<pnet->get<LmsNetAttributes>().learningRate<<"\n";

    //Add full connectiovity output layer
    const vector<NeuronPtr>& output_neurons = *(pnet->getCache().layers.end() - 2);
    for(unsigned i = 0; i < men; ++i)
    {
        NeuronPtr n(NeuronFactory::PyramidalNeuron(TanH::Instance()));
        for(unsigned j = 0; j < output_neurons.size(); ++j)
            pnet->addConnection(output_neurons[j], n);
    }

    pnet->get<WeightRandomizationAttributes>().min = -0.1;
    pnet->get<WeightRandomizationAttributes>().max = +0.1;
    pnet->run(RandomizeWeightsGaussRunner::Instance());
    pnet->setWorkThreadsCount(0); //unleash the power of double quad core Xeon (c)

    //Formatting TrainData from raw_data
    TrainData all_data;
    unsigned total_img = 0;
    for(unsigned i = 0; i < orl.size(); ++i)
    {
        if(orl[i].man > men || orl[i].pose != 1)
            continue;

        total_img++;

        all_data.push_back(imgm2tp(orl[i], men));
    }
    shuffle(all_data);
    cout<<"Prepared "<<total_img<<" images\n";
    pair<TrainData, TrainData> bunch = divide(all_data, 0);
    TrainData train_data, test_data;
    train_data = bunch.first; //60%
    test_data = bunch.second; //40%

    /*
    for(int p = 1; p < 20; p++)
    {
    pnet->setWorkThreadsCount(p); //unleash the power of double quad core Xeon (c)
#ifdef UNIX
        struct timeval start, stop;
        gettimeofday(&start, 0);
#endif
    */

    //Trainig net
    cout<<"Training for "<<epochs<<" epochs\n";
    for(unsigned i = 1; i <= epochs; ++i)
    {
        shuffle(train_data);
        Lms::train(pnet, train_data);
        test(pnet, test_data);
        cout<<i<<"\t"<<ErrorFunction::mse(train_data)<<"\t"<<ErrorFunction::mse(test_data)<<"\n";
    }
    /*
#ifdef UNIX
        gettimeofday(&stop, 0);
        cout<<"Processes: "<<p<<"\tTimeDiff: "<<(stop.tv_sec-start.tv_sec)<<"sec "<<(stop.tv_usec-start.tv_usec)<<"usec\n\n";
#endif
    }
    */

    //Print detailed test results
    cout<<"Detailed test results\n";
    unsigned count = 0;
    do {
        //Select 20 images from ORL faces
        unsigned id = std::rand() % orl.size();
        if(orl[id].man > men)
            continue;

        count++;

        //Convert image to TrainPattern
        TrainPattern tp = imgm2tp(orl[id], men);

        //Process it
        pnet->setInput(tp.input());
        pnet->run(FeedforwardPropagationRunner::Instance());
        pnet->getOutput(tp.actual_output());

        //Print detailed info about image and MSE
        cout<<"\nMan:\t"<<orl[id].man \
            <<"\nPose:\t"<<orl[id].pose \
            <<"\nShift:\t"<<orl[id].shift \
            <<"\nNoise:\t"<<orl[id].noise \
            <<"\nError:\t"<<ErrorFunction::mse(tp)<<"\n";

        //Print actual network output
        for(unsigned j = 0; j < men; ++j)
            cout<<j+1<<":\t"<<tp.desired_output()[j]<<" "<<tp.actual_output()[j]<<" "<<tp.error()[j]<<"\n";
        cout<<"\n";
    } while(count < 20);

    Storage::save<Storage::txt_out>(pnet, "Exp3.net");
} //experiment3
#endif


/*
 * Большая сверточная сеть, по 1 выходному нейрону на человека
 * Постепенно добавляем нейроны
 */
#if EXP==4
void experiment4()
{
    unsigned const men = 5;
    unsigned const epochs = 10;
    vector<unsigned> planes;
    planes += 20,50,men;
    NetPtr pnet = ConvolutionalNetwork(planes, 0.4);

    pnet->get<LmsNetAttributes>().learningRate = 0.3;
    pnet->get<LmsNetAttributes>().annealingTSC = 20000; //inf
    pnet->get<WeightRandomizationAttributes>().min = -0.1;
    pnet->get<WeightRandomizationAttributes>().max = +0.1;
    pnet->run(RandomizeWeightsGaussRunner::Instance());
    pnet->setWorkThreadsCount(0); //unleash the power of double quad core Xeon (c)

    //Formatting TrainData from raw_data
    TrainData all_data;
    unsigned total_img = 0;
    for(unsigned i = 0; i < orl.size(); ++i)
    {
        if(orl[i].man > men)
            continue;

        total_img++;

        all_data.push_back(imgm2tp(orl[i], men));
    }
    shuffle(all_data);
    cout<<"Prepared "<<total_img<<" images\n";
    pair<TrainData, TrainData> bunch = divide(all_data, 60);
    TrainData train_data, test_data;
    train_data = bunch.first; //60%
    test_data = bunch.second; //40%

    //Trainig net
    cout<<"Training for "<<epochs<<" epochs\n";
    for(unsigned i = 1; i <= epochs; ++i)
    {
        shuffle(train_data);
        Lms::train(pnet, train_data);
        test(pnet, test_data);
        cout<<i<<"\t"<<ErrorFunction::mse(train_data)<<"\t"<<ErrorFunction::mse(test_data)<<"\n";
    }

    //Print detailed test results
    cout<<"Detailed test results\n";
    unsigned count = 0;
    do {
        //Select 20 images from ORL faces
        unsigned id = std::rand() % orl.size();
        if(orl[id].man > men)
            continue;

        count++;

        //Convert image to TrainPattern
        TrainPattern tp = imgm2tp(orl[id], men);

        //Process it
        pnet->setInput(tp.input());
        pnet->run(FeedforwardPropagationRunner::Instance());
        pnet->getOutput(tp.actual_output());

        //Print detailed info about image and MSE
        cout<<"\nMan:\t"<<orl[id].man \
            <<"\nPose:\t"<<orl[id].pose \
            <<"\nShift:\t"<<orl[id].shift \
            <<"\nNoise:\t"<<orl[id].noise \
            <<"\nError:\t"<<ErrorFunction::mse(tp)<<"\n";

        //Print actual network output
        for(unsigned j = 0; j < men; ++j)
            cout<<j+1<<":\t"<<tp.desired_output()[j]<<" "<<tp.actual_output()[j]<<" "<<tp.error()[j]<<"\n";
        cout<<"\n";
    } while(count < 20);

    Storage::save<Storage::txt_out>(pnet, "Exp3.net");
} //experiment4
#endif

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout<<"Usage: "<<argv[0]<<" <file_list>\n";
        return -1;
    }

    //Processing images
    readImages(argv[1], orl);

    EXPERIMENT();

    //Debug
    /*
    vector<unsigned> planes;
    planes += 10,50,250;
    NetPtr net = MirrorConvolutionalNetwork(planes, 1.0, 5,5, 3,3);

    cout<<"Net cache:\n";
    const NetCache& cache = net->getCache();
    for(unsigned i = 0; i < cache.layers.size(); ++i)
        cout<<cache.layers[i].size()<<endl;
    cout<<endl;

    //Saving topology for viewing
    Storage::save<Storage::bin_out>(*net, "mirror_network.net");
    */

    return 0;
}

