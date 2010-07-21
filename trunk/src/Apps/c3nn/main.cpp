
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

#include "pann-shit.h"
#include "config.h"
#include "util.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

int main(int argc, char ** argv)
{
    random_seed(time(0));

    if(argc < 2) {
        cout<<"Usage: "<<argv[0]<<" <config-file-path>"<<endl;
        return -1;
    }

    ConfigT cfg;
    try {
        cfg = configure(argv[1]);
    } catch (std::exception e) {
        cout<<"Error while reading configuration data\n"<<e.what()<<endl;
        return -1;
    }

    cfg.print();

    vector<FaceT> orl = make_faces(cfg);
    vector<NetPtr> nets = make_nets(cfg);

    /*
    trace(nets[0]);

    TrainPattern tmp(4, 1);
    for(unsigned i = 0; i < 4; ++i) {
        tmp.input()[i] = 1;
    }

    nets[0]->set_input(tmp.input());
    nets[0]->run(FeedforwardPropagationRunner::Instance());
    nets[0]->get_output(tmp.actual_output()); //actual output
    cout<<tmp.input()[0]<<" "<<tmp.actual_output()[0]<<endl;
    */

    TrainData all_data;
    unsigned total_img = 0;
    for(unsigned i = 0; i < orl.size(); ++i)
    {
        if(orl[i].man > cfg.faces.men)
            continue;

        total_img++;

        all_data.push_back(imgm2tp(orl[i], cfg.faces.men));
    }
    shuffle(all_data);
    cout<<"Prepared "<<total_img<<" images\n";
    pair<TrainData, TrainData> bunch = divide(all_data, 100 - cfg.faces.train_percent);
    TrainData train_data, test_data;
    train_data = bunch.first;
    test_data = bunch.second;
    cout<<"Train/test: "<<train_data.size()<<"/"<<test_data.size()<<"\n";

    //TODO: LMS!!
    cout<<"Training for "<<cfg.lms.epochs<<" epochs\n";
    for(unsigned i = 1; i <= cfg.lms.epochs; ++i)
    {
        shuffle(train_data);
        unsigned net_no = 0;
        BOOST_FOREACH(const NetPtr & pnet, nets) {
            Lms::train(pnet, train_data);
            test(pnet, test_data);
            Float test_err = ErrorFunction::mse(test_data);
            cout<<"epoch="<<i<<" net="<<net_no++<<" train_err="<<ErrorFunction::mse(train_data)<<
                " test_err="<<test_err<<"\n";
            if(test_err < cfg.faces.stop_error)
                break;
        }
    }

    cout<<"Detailed test results\n";
    BOOST_FOREACH(const NetPtr & pnet, nets) {
        unsigned count = 0;
        do {
            //Select 20 images from ORL faces
            unsigned id = std::rand() % orl.size();
            if(orl[id].man > cfg.faces.men || orl[id].position != 1)
                continue;

            count++;

            //Convert image to TrainPattern
            TrainPattern tp = imgm2tp(orl[id], cfg.faces.men);

            //Process it
            pnet->set_input(tp.input());
            pnet->run(FeedforwardPropagationRunner::Instance());
            pnet->get_output(tp.actual_output());

            //Print detailed info about image and MSE
            cout<<"\nMan:\t"<<orl[id].man \
                <<"\nPosition:\t"<<orl[id].position \
                <<"\nError:\t"<<ErrorFunction::mse(tp)<<"\n";

            //Print actual network output
            for(unsigned j = 0; j < cfg.faces.men; ++j)
                cout<<j+1<<":\t"<<tp.desired_output()[j]<<" "<<tp.actual_output()[j]<<" "<<tp.error()[j]<<"\n";
            cout<<"\n";
        } while(count < 20);

        //Storage::save<Storage::txt_out>(pnet, "Exp3.net");
    }

    return 0;
}; //main

