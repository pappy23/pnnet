
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
    Image *img;
};

void readImages(const char* _listfile, vector<ImageWithMetadata>& _data);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout<<"Usage: "<<argv[0]<<" <file_list>\n";
        return -1;
    }

    vector<unsigned> planes;
    planes += 1,1,1;
    Model netm_left  = ConvolutionalNetworkModel(planes, 1.0, 5,5, 3,3);
    Model netm_right = ConvolutionalNetworkModel(planes, 1.0, 5,5, 3,3);

    Net net;
    unsigned last_layer = netm_left.size() - 1;
    for(unsigned i = 0; i < netm_left[last_layer].size(); ++i)
        net.addConnection(netm_left[last_layer][i][0][0], netm_right[last_layer][i][0][0]);

    for(unsigned i = 0; i < netm_left[0][0].size(); ++i)
    {
        for(unsigned j = 0; j < netm_left[0][0][i].size(); ++j)
            net.addInputNeuron(netm_left[0][0][i][j]);
    }

    Storage::save<Storage::txt_out>(net, "mirror_network.net");

    vector<ImageWithMetadata> orl;
    readImages(argv[1], orl);

    /*
    Test1.
    постановка эксперимента:
    1)строим сверточную сеть с конфигурацией
    95x95
    46x46 46x46
    23x23 23x23
    10x10 10x10
    5x5 5x5
    1x1 1x1

    2)строим вторую такую же сеть
    3) соединяем выходные нейроны обоих сетей

    N1 --> N1'
    N2 --> N2'
    Т.е. не каждый с каждым

    4)загружаем картинки 1 человека (10 ракурсов, вариант с малым шумом и без
    шума. Каждый ракурс - по 4 варианта)
    5)выбираем из всех фоток одну без шума, в анфас. Это будет эталон
    6)учим сеть, показывая фотки на входе и требуя на выходе эталон
    7)из фоток отбирается 20% на тесты
    8)строим график ошибки для множества обучения и множества тестового
    9)делаем выводы

    Вариант 2:
    Учим не на эталоне, а на куче комбинаций
    */


    return 0;
}

void readImages(const char* _listfile, vector<ImageWithMetadata>& _data)
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

