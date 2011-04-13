
#include "pann-shit.h"
#include "config.h"
#include "util.h"

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

using namespace std;
using namespace boost;
using namespace pann;


//All faces are stored here
map<unsigned, FaceT> faces;
map<unsigned, DatasetT> datasets;

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
    xmlrpc_value * item;
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
    xmlrpc_value * item;
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
    xmlrpc_value * item;

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


int main(int argc, char ** argv)
{
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

    faces = make_faces(cfg);
//    for(map<unsigned, FaceT>::iterator it = faces.begin(); it != faces.end(); ++it)
//        cout<<it->first<<" "<<it->second.id<<" "<<imgm2tp(it->second, 5).desired_output().size()<<endl;
//        cout<<it->first<<" "<<it->second.id<<" "<<it->second.img->getAverageValarray().size()<<endl;
    make_datasets(datasets, cfg, faces);

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

//    xmlrpc_registry_add_method(&env, registryP, NULL, "faces.get_conut", &faces_get_count, NULL);

    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = cfg.rpc_port;
    serverparm.log_file_name    = "/tmp/xmlrpc_log";

    printf("Running XML-RPC server...\n");

    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));


    return 0;
}; //main

