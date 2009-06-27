
#include "pann.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;
using namespace pann::ConvolutionalNetworkTypes;

struct ImageWithMetadata
{
    unsigned man; // 1 - 40
    unsigned pose; // 1 - 10
    unsigned shift; // 1 - 4
    unsigned noise; //0 - no noise, 1 -  small noise
    Image *img; //Pointer, becase Image lacks default constructor
};

//ORL-faces database
//@see main()
vector<ImageWithMetadata> orl;

/**
 * Build Mirror Convolutional Network topology
 * @see ConvolutionalNetwork()
 */
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
        tp.input = raw_data[i].img->getAverageValarray();
        squash(tp.input, 0.0, 255.0, -1.8, +1.8);
        tp.desired_output = template_img.img->getAverageValarray();
        squash(tp.desired_output, 0.0, 255.0, -1.8, +1.8);
        tdata.data.push_back(tp);
    }

    //Test run
    cout<<"Test run\n";
    pnet->setInput(tdata.data[0].input);
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
        tdata.shuffle();
        Lms::train(pnet, tdata);
        cout<<i<<"\t"<<tdata.getMse()<<"\n";
    }

    Storage::save<Storage::txt_out>(pnet, "MirrorConvNet_Exp1.net");
} //experiment1

/*
 * Строим сверточную сеть которая запоминает одного человека
 * И только его
 */
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
        if(orl[i].man > 3 || orl[i].pose != 1 || orl[i].shift != 1)
            continue;

        TrainPattern tp(95*95, 2);
        tp.input = orl[i].img->getAverageValarray();
        squash(tp.input, 0.0, 255.0, -1.8, +1.8);
        if(1 == orl[i].man)
        {
            tp.desired_output[0] = 1.8;
            tp.desired_output[1] = -1.8;
        } else {
            tp.desired_output[0] = -1.8;
            tp.desired_output[1] = 1.8;
        }
        tdata.data.push_back(tp);
    }

    //Trainig net
    pnet->get<LmsNetAttributes>().learningRate = 0.1;
    pnet->get<LmsNetAttributes>().annealingTSC = 10;
    pnet->get<WeightRandomizationAttributes>().min = -0.2;
    pnet->get<WeightRandomizationAttributes>().max = +0.2;
    pnet->run(RandomizeWeightsGaussRunner::Instance());
    pnet->setWorkThreadsCount(1);

    unsigned const epochs = 10;
    cout<<"Training for "<<epochs<<" epochs\n";
    for(unsigned i = 1; i < epochs; ++i)
    {
        tdata.shuffle();
        Lms::train(pnet, tdata);
        cout<<i<<"\t"<<tdata.getMse()<<"\n";
    }

    Storage::save<Storage::txt_out>(pnet, "Exp2.net");
} //experiment2

/*
 * Большая сверточная сеть, по 1 выходному нейрону на человека
 * Отделяем тестовое множество и учим сеть
 */
void experiment3()
{
    vector<unsigned> planes;
    planes += 20,50,40;
    NetPtr pnet = ConvolutionalNetwork(planes, 0.8);

    pnet->get<LmsNetAttributes>().learningRate = 0.1;
    pnet->get<LmsNetAttributes>().annealingTSC = 10;
    pnet->get<WeightRandomizationAttributes>().min = -0.2;
    pnet->get<WeightRandomizationAttributes>().max = +0.2;
    pnet->run(RandomizeWeightsGaussRunner::Instance());
    pnet->setWorkThreadsCount(0); //unleash the power of double quad core Xeon (c)
    unsigned const epochs = 10;

    //Formatting TrainData from raw_data
    TrainData all_data;
    for(unsigned i = 0; i < orl.size(); ++i)
    {
        TrainPattern tp(95*95, 40);
        tp.input = orl[i].img->getAverageValarray();
        squash(tp.input, 0.0, 255.0, -1.8, +1.8);
        for(unsigned j = 0; j < 40; ++j)
            tp.desired_output[j] = -1.8;
        tp.desired_output[orl[i].man - 1] = +1.8;
        all_data.data.push_back(tp);
    }
    pair<vector<TrainPattern>, vector<TrainPattern> > bunch = DataGenerator::divide(all_data.data, 20);
    TrainData train_data, test_data;
    train_data.data = bunch.first; //80%
    test_data.data = bunch.second; //20%

    //Trainig net
    cout<<"Training for "<<epochs<<" epochs\n";
    for(unsigned i = 1; i <= epochs; ++i)
    {
        train_data.shuffle();
        Lms::train(pnet, train_data);
        test(pnet, test_data);
        cout<<i<<"\t"<<train_data.getMse()<<"\t"<<test_data.getMse()<<"\n";
    }

    //Print detailed test results
    cout<<"Detailed test results\n";
    for(unsigned i = 0; i < 20; ++i)
    {
        //Select 20 images from ORL faces
        unsigned id = std::rand() % orl.size();

        //Convert image to TrainPattern
        TrainPattern tp(95*95, 40);
        tp.input = orl[id].img->getAverageValarray();
        squash(tp.input, 0.0, 255.0, -1.8, +1.8);
        for(unsigned j = 0; j < 40; ++j)
            tp.desired_output[j] = -1.8;
        tp.desired_output[orl[id].man - 1] = +1.8;

        //Process it
        pnet->setInput(tp.input);
        pnet->run(FeedforwardPropagationRunner::Instance());
        valarray<Float> output;
        pnet->getOutput(output);
        tp.error = tp.desired_output - output;

        //Print detailed info about image and MSE
        cout<<"\nMan:\t"<<orl[id].man \
            <<"\nPose:\t"<<orl[id].pose \
            <<"\nShift:\t"<<orl[id].shift \
            <<"\nNoise:\t"<<orl[id].noise \
            <<"\nError:\t"<<tp.getMse();

        //Print actual network output
        for(unsigned j = 0; j < 40; ++j)
            cout<<j<<":\t"<<output[j]<<"\n";
        cout<<"\n";
    }

    Storage::save<Storage::txt_out>(pnet, "Exp3.net");
} //experiment3

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout<<"Usage: "<<argv[0]<<" <file_list>\n";
        return -1;
    }

    //Processing images
    readImages(argv[1], orl);

    experiment3();

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

