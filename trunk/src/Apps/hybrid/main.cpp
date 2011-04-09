
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
vector<FaceT> orl;

static xmlrpc_value * faces_get_count(  xmlrpc_env *   const envP,
                                        xmlrpc_value * const paramArrayP,
                                        void *         const serverInfo,
                                        void *         const channelInfo) {
//                                        void *         const user_data) {

    //xmlrpc_int32 x, y, z;

    /* Parse our argument array. */
    //xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &x, &y);
    //if (envP->fault_occurred)
    //return NULL;

    /* Add our two numbers. */
    //z = x + y;

    /* Return our result. */
    return xmlrpc_build_value(envP, "i", orl.size()); 
}


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

    orl = make_faces(cfg);

//New XML-RPC only
    struct xmlrpc_method_info3 const methodInfo = {
        /* .methodName     = */ "faces.get_count",
        /* .methodFunction = */ &faces_get_count,
    };
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;
    xmlrpc_env env;

    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);

    xmlrpc_registry_add_method3(&env, registryP, &methodInfo);
//    xmlrpc_registry_add_method(&env, registryP, NULL, "faces.get_conut", &faces_get_count, NULL);

    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = cfg.rpc_port;
    serverparm.log_file_name    = "/tmp/xmlrpc_log";

    printf("Running XML-RPC server...\n");

    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));


    return 0;
}; //main

