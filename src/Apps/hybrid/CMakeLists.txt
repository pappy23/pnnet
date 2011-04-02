
add_executable(rpcsrv main.cpp config.cpp util.cpp)
target_link_libraries(rpcsrv pann-shit xmlrpc xmlrpc_cpp xmlrpc_util xmlrpc_server xmlrpc_server_abyss)

