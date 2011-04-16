
#include "pann-shit.h"
#include "config.h"
#include "util.h"

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

using namespace std;
using namespace boost;
using namespace pann;


ConfigT cfg;
map<unsigned, FaceT> faces;
map<unsigned, DatasetT> datasets;
map<unsigned, NetT> nets;

static xmlrpc_value * rpc_faces_get_count(  xmlrpc_env *   const envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {

    /* Return our result. */
    return xmlrpc_build_value(envP, "i", faces.size());
}; //rpc_faces_get_count

static xmlrpc_value * rpc_faces_get_id_list(xmlrpc_env *   const envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {
    xmlrpc_value * result = xmlrpc_array_new(envP);
    for(map<unsigned, FaceT>::iterator it = faces.begin(); it != faces.end(); ++it) {
        xmlrpc_value * item = xmlrpc_build_value(envP, "i", it->first);
        xmlrpc_array_append_item(envP, result, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "A", result);
}; //rpc_faces_get_id_list

static xmlrpc_value * rpc_faces_get_face(xmlrpc_env *   const envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {
    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);

    if(faces.find(id) == faces.end()) {
        xmlrpc_faultf(envP, "Face %d not found", id);
        return 0;
    }

    return xmlrpc_build_value(envP, "{s:i,s:i,s:i,s:s}", "id", faces[id].id, "man", faces[id].man, "position", faces[id].position, "path", faces[id].path.c_str());
}; //rpc_faces_get_face

static xmlrpc_value * rpc_datasets_get_id_list(xmlrpc_env *   const envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {
    xmlrpc_value * result = xmlrpc_array_new(envP);
    for(map<unsigned, DatasetT>::iterator it = datasets.begin(); it != datasets.end(); ++it) {
        xmlrpc_value * item = xmlrpc_build_value(envP, "i", it->first);
        xmlrpc_array_append_item(envP, result, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "A", result);
}; //rpc_datasets_get_id_list

static xmlrpc_value * rpc_datasets_get_dataset(xmlrpc_env *  envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {

    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);
    xmlrpc_value * face_ids = xmlrpc_array_new(envP);

    if(datasets.find(id) == datasets.end()) {
        xmlrpc_faultf(envP, "Dataset %d not found", id);
        return 0;
    }

    for(unsigned i = 0; i < datasets[id].face_ids.size(); ++i) {
        xmlrpc_value * item = xmlrpc_build_value(envP, "i", datasets[id].face_ids[i]);
        xmlrpc_array_append_item(envP, face_ids, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "{s:i,s:s,s:A}", "id", datasets[id].id, "name", datasets[id].name.c_str(), "face_ids", face_ids);
}; //rpc_datasets_get_dataset

static xmlrpc_value * rpc_nets_get_id_list(xmlrpc_env *   const envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {
    xmlrpc_value * result = xmlrpc_array_new(envP);
    for(map<unsigned, NetT>::iterator it = nets.begin(); it != nets.end(); ++it) {
        xmlrpc_value * item = xmlrpc_build_value(envP, "i", it->first);
        xmlrpc_array_append_item(envP, result, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "A", result);
}; //rpc_nets_get_id_list

static xmlrpc_value * rpc_nets_get_net(xmlrpc_env *  envP,
        xmlrpc_value * const paramArrayP,
        void *         const serverInfo,
        void *         const channelInfo) {

    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);

    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }

    bool is_loaded = false;
    if(nets[id].p)
        is_loaded = true;

    return xmlrpc_build_value(envP, "{s:i,s:s,s:s,s:b,s:b}",
            "id", nets[id].id,
            "name", nets[id].name.c_str(),
            "path", nets[id].path.c_str(),
            "actual", nets[id].actual,
            "loaded", is_loaded);
}; //rpc_nets_get_net

static xmlrpc_value * rpc_nets_get_size(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {

    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);

    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }
    if(!nets[id].p) {
        xmlrpc_faultf(envP, "Net %d not loaded", id);
        return 0;
    }

    xmlrpc_value * result = xmlrpc_array_new(envP);
    const NetCache & cache = nets[id].p->get_cache();
    for(unsigned i = 0; i < cache.layers.size(); ++i) {
        xmlrpc_value * item = xmlrpc_build_value(envP, "i", cache.layers[i].size());
        xmlrpc_array_append_item(envP, result, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "A", result);
}; //rpc_nets_get_size

static xmlrpc_value * rpc_nets_create_mlp(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {

    //STUB
    save_nets_info(nets, cfg);
    return xmlrpc_build_value(envP, "i", 1);
}; //rpc_nets_create_mlp

static xmlrpc_value * rpc_nets_create_convnet(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {

    //STUB
    save_nets_info(nets, cfg);
    return xmlrpc_build_value(envP, "i", 1);
}; //rpc_nets_create_convnet

static xmlrpc_value * rpc_nets_create_gcnn(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {

    //STUB
    save_nets_info(nets, cfg);
    return xmlrpc_build_value(envP, "i", 1);
}; //rpc_nets_create_gcnn

static xmlrpc_value * rpc_nets_copy(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {

    //STUB
    save_nets_info(nets, cfg);
    return xmlrpc_build_value(envP, "i", 1);
}; //rpc_nets_copy

static xmlrpc_value * rpc_nets_rename(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id;
    const char * name;
    xmlrpc_decompose_value(envP, paramArrayP, "(is)", &id, &name);

    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }

    nets[id].name = name;
    save_nets_info(nets, cfg);

    return xmlrpc_build_value(envP, "i", 0);
}; //rpc_nets_rename

static xmlrpc_value * rpc_nets_load(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }
    if(nets[id].p) {
        // net already loaded
    }

    string path = cfg.net_list_path_base;
    path += "/";
    path += nets[id].path;
    try {
        Storage::load<Storage::txt_in>(nets[id].p, path.c_str());
    } catch (...) {
        xmlrpc_faultf(envP, "IO error while reading %s", path.c_str());
        nets[id].p.reset();
        return 0;
    }
    nets[id].actual = true;

    return xmlrpc_build_value(envP, "i", 0);
}; //rpc_nets_load

static xmlrpc_value * rpc_nets_save(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }
    if(!nets[id].p) {
        xmlrpc_faultf(envP, "Net %d not loaded", id);
        return 0;
    }

    string path = cfg.net_list_path_base;
    path += "/";
    path += nets[id].path;
    try {
        Storage::save<Storage::txt_out>(nets[id].p, path.c_str());
    } catch (...) {
        xmlrpc_faultf(envP, "IO error while writing %s", path.c_str());
        return 0;
    }
    nets[id].actual = true;

    return xmlrpc_build_value(envP, "i", 0);
}; //rpc_nets_save

static xmlrpc_value * rpc_nets_delete(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id;
    xmlrpc_decompose_value(envP, paramArrayP, "(i)", &id);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }

    dispose_net(nets[id].p); //free occupied memory
    //delete net file from disk - not implemented
    nets.erase(id);
    save_nets_info(nets, cfg);

    return xmlrpc_build_value(envP, "i", 0);
}; //rpc_nets_delete

static xmlrpc_value * rpc_nets_reset(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id;
    xmlrpc_double min, max;
    xmlrpc_decompose_value(envP, paramArrayP, "(idd)", &id, &min, &max);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }

    nets[id].actual = false;
    randomize_weights_gauss(nets[id].p, min, max);

    return xmlrpc_build_value(envP, "i", 0);
}; //rpc_nets_reset

static xmlrpc_value * rpc_nets_test1(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id, face_id;
    xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &id, &face_id);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }
    if(!nets[id].p) {
        xmlrpc_faultf(envP, "Net %d not loaded", id);
        return 0;
    }
    if(faces.find(face_id) == faces.end()) {
        xmlrpc_faultf(envP, "Face %d not found", face_id);
        return 0;
    }
    unsigned men = get_output_number(nets[id].p);
    if(faces[face_id].man > men) {
        xmlrpc_faultf(envP, "Not enough outputs (%d) to process face with man=%d", men, faces[face_id].man);
        return 0;
    }

    TrainPattern tp = imgm2tp(faces[face_id], men);
    nets[id].p->set_input(tp.input());
    nets[id].p->run(FeedforwardPropagationRunner::Instance());
    nets[id].p->get_output(tp.actual_output());

    xmlrpc_value * result = xmlrpc_array_new(envP);
    for(unsigned i = 0; i < men; ++i) {
        xmlrpc_value * item = xmlrpc_build_value(envP, "{s:d,s:d,s:d}",
                "desired_output", tp.desired_output()[i],
                "actual_output", tp.actual_output()[i],
                "error", tp.error()[i]);
        xmlrpc_array_append_item(envP, result, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "dA", ErrorFunction::mse(tp), result);
}; //rpc_nets_test1

static xmlrpc_value * rpc_nets_test_set(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {

    xmlrpc_int32 id, dataset_id;
    xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &id, &dataset_id);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }
    if(!nets[id].p) {
        xmlrpc_faultf(envP, "Net %d not loaded", id);
        return 0;
    }
    if(datasets.find(dataset_id) == datasets.end()) {
        xmlrpc_faultf(envP, "Dataset %d not found", dataset_id);
        return 0;
    }
    if(!check_dataset(nets[id].p, datasets[dataset_id], faces)) {
        xmlrpc_faultf(envP, "Number of faces in dataset and number of outputs doesn't match");
        return 0;
    }

    test(nets[id].p, datasets[dataset_id].td);

    return xmlrpc_build_value(envP, "d", ErrorFunction::mse(datasets[dataset_id].td));
}; //rpc_nets_test_set

static xmlrpc_value * rpc_nets_teach(xmlrpc_env * envP,
                               xmlrpc_value * const paramArrayP,
                               void * const serverInfo, void * const channelInfo
                    ) {
    xmlrpc_int32 id, train_set_id, test_set_id, epochs;
    xmlrpc_double stop_error;

    xmlrpc_decompose_value(envP, paramArrayP, "(iiiid)", &id, &train_set_id, &test_set_id, &epochs, &stop_error);
    if(nets.find(id) == nets.end()) {
        xmlrpc_faultf(envP, "Net %d not found", id);
        return 0;
    }
    if(!nets[id].p) {
        xmlrpc_faultf(envP, "Net %d not loaded", id);
        return 0;
    }
    if(datasets.find(train_set_id) == datasets.end()) {
        xmlrpc_faultf(envP, "Dataset %d not found", train_set_id);
        return 0;
    }
    if(!check_dataset(nets[id].p, datasets[train_set_id], faces)) {
        xmlrpc_faultf(envP, "Number of faces in train dataset and number of outputs doesn't match");
        return 0;
    }
    if(datasets.find(test_set_id) == datasets.end()) {
        xmlrpc_faultf(envP, "Dataset %d not found", test_set_id);
        return 0;
    }
    if(!check_dataset(nets[id].p, datasets[test_set_id], faces)) {
        xmlrpc_faultf(envP, "Number of faces in test dataset and number of outputs doesn't match");
        return 0;
    }

    nets[id].actual = false;

    TrainData & train_data = datasets[train_set_id].td;
    TrainData & test_data  = datasets[test_set_id].td;

    xmlrpc_value * result = xmlrpc_array_new(envP);

    bool need_to_stop = false;
    for(unsigned i = 1; i <= epochs; ++i)
    {
        if(need_to_stop)
            break;

        shuffle(train_data);
        Lms::train(nets[id].p, train_data);
        test(nets[id].p, test_data);

        Float test_err = ErrorFunction::mse(test_data);
        if(test_err < stop_error)
            need_to_stop = true;

        xmlrpc_value * item = xmlrpc_build_value(envP, "{s:i,s:d,s:d}",
                "epoch", i,
                "train_error", ErrorFunction::mse(train_data),
                "test_err", test_err);
        xmlrpc_array_append_item(envP, result, item);
        xmlrpc_DECREF(item);
    }

    return xmlrpc_build_value(envP, "A", result);
}; //rpc_nets_teach

int main(int argc, char ** argv)
{
    if(argc < 2) {
        cout<<"Usage: "<<argv[0]<<" <config-file-path>"<<endl;
        return -1;
    }

    try {
        cfg = configure(argv[1]);
    } catch (std::exception e) {
        cout<<"Error while reading configuration data\n"<<e.what()<<endl;
        return -1;
    }

    cfg.print();

    faces = make_faces(cfg);
    make_datasets(datasets, cfg, faces);
    make_nets(nets, cfg);
    save_nets_info(nets, cfg);

    //New XML-RPC only
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;
    xmlrpc_env env;
    xmlrpc_env_init(&env);
    registryP = xmlrpc_registry_new(&env);

    struct xmlrpc_method_info3 const rpc_faces_get_count_m = {
        /* .methodName     = */ "faces.get_count",
        /* .methodFunction = */ &rpc_faces_get_count,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_faces_get_count_m);

    struct xmlrpc_method_info3 const rpc_faces_get_id_list_m = {
        /* .methodName     = */ "faces.get_id_list",
        /* .methodFunction = */ &rpc_faces_get_id_list,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_faces_get_id_list_m);

    struct xmlrpc_method_info3 const rpc_faces_get_face_m = {
        /* .methodName     = */ "faces.get_face",
        /* .methodFunction = */ &rpc_faces_get_face,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_faces_get_face_m);

    struct xmlrpc_method_info3 const rpc_datasets_get_id_list_m = {
        /* .methodName     = */ "datasets.get_id_list",
        /* .methodFunction = */ &rpc_datasets_get_id_list,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_datasets_get_id_list_m);

    struct xmlrpc_method_info3 const rpc_datasets_get_dataset_m = {
        /* .methodName     = */ "datasets.get_dataset",
        /* .methodFunction = */ &rpc_datasets_get_dataset,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_datasets_get_dataset_m);

    struct xmlrpc_method_info3 const rpc_nets_get_id_list_m = {
        /* .methodName     = */ "nets.get_id_list",
        /* .methodFunction = */ &rpc_nets_get_id_list,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_get_id_list_m);

    struct xmlrpc_method_info3 const rpc_nets_get_net_m = {
        /* .methodName     = */ "nets.get_net",
        /* .methodFunction = */ &rpc_nets_get_net,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_get_net_m);

    struct xmlrpc_method_info3 const rpc_nets_get_size_m = {
        /* .methodName     = */ "nets.get_size", // (int id) -> ([int layer_size])
        /* .methodFunction = */ &rpc_nets_get_size,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_get_size_m);

    struct xmlrpc_method_info3 const rpc_nets_create_mlp_m = {
        /* .methodName     = */ "nets.create_mlp", // ([int layer_size]) -> (int id)
        /* .methodFunction = */ &rpc_nets_create_mlp,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_create_mlp_m);

    struct xmlrpc_method_info3 const rpc_nets_create_convnet_m = {
        /* .methodName     = */ "nets.create_convnet", // (float density, int wh, int ww, int who, int wwo, [int layer_size]) -> (int id)
        /* .methodFunction = */ &rpc_nets_create_convnet,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_create_convnet_m);

    struct xmlrpc_method_info3 const rpc_nets_create_gcnn_m = {
        /* .methodName     = */ "nets.create_gcnn", // ???
        /* .methodFunction = */ &rpc_nets_create_gcnn,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_create_gcnn_m);

    struct xmlrpc_method_info3 const rpc_nets_copy_m = {
        /* .methodName     = */ "nets.copy", // (int id) -> (int id)
        /* .methodFunction = */ &rpc_nets_copy,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_copy_m);

    struct xmlrpc_method_info3 const rpc_nets_rename_m = {
        /* .methodName     = */ "nets.rename", // (int id, string name)
        /* .methodFunction = */ &rpc_nets_rename,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_rename_m);

    struct xmlrpc_method_info3 const rpc_nets_load_m = {
        /* .methodName     = */ "nets.load", // (int id)
        /* .methodFunction = */ &rpc_nets_load,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_load_m);

    struct xmlrpc_method_info3 const rpc_nets_save_m = {
        /* .methodName     = */ "nets.save", // (int id)
        /* .methodFunction = */ &rpc_nets_save,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_save_m);

    struct xmlrpc_method_info3 const rpc_nets_delete_m = {
        /* .methodName     = */ "nets.delete", // (int id)
        /* .methodFunction = */ &rpc_nets_delete,
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_delete_m);

    struct xmlrpc_method_info3 const rpc_nets_reset_m = {
        /* .methodName     = */ "nets.reset", // Randomize weights
        /* .methodFunction = */ &rpc_nets_reset, // (int id)
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_reset_m);

    struct xmlrpc_method_info3 const rpc_nets_test1_m = {
        /* .methodName     = */ "nets.test1", // feed net with one face and get detailed output
        /* .methodFunction = */ &rpc_nets_test1, // (int id, int face_id) -> (float mse_error, [(desired_output, actual_output, error)])
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_test1_m);

    struct xmlrpc_method_info3 const rpc_nets_test_set_m = {
        /* .methodName     = */ "nets.test_set", //test net on set of images and get error value
        /* .methodFunction = */ &rpc_nets_test_set, //(int id, int dataset_id) -> (float mse_error)
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_test_set_m);

    struct xmlrpc_method_info3 const rpc_nets_teach_m = {
        /* .methodName     = */ "nets.teach", // (int id, int learning_dataset_id, int testing_dataset_id, int epochs, float stop_error) ->
        /* .methodFunction = */ &rpc_nets_teach, // ([int epoch, float learn_error, float test_error])
    };
    xmlrpc_registry_add_method3(&env, registryP, &rpc_nets_teach_m);

//    xmlrpc_registry_add_method(&env, registryP, NULL, "faces.get_conut", &faces_get_count, NULL);

    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = cfg.rpc_port;
    serverparm.log_file_name    = "/tmp/xmlrpc_log";

    printf("Running XML-RPC server...\n");

    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));


    return 0;
}; //main

