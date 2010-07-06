
#include <iostream>
#include <fstream>
#include <cstring>
#include <boost/lexical_cast.hpp>

#include "pann.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "config.h"

using namespace std;
using namespace pann;
using namespace rapidxml;
using boost::lexical_cast;

const unsigned MAX_FILESIZE = 10000;

void configure(const char * filename)
{
    ConfigT config;

    try {
        rapidxml::file<> xmlfile(filename);
        xml_document<> doc;
        doc.parse<0>(xmlfile.data());

        xml_node<> *root = doc.first_node("config");
        for(xml_node<> *child = root->first_node(); child; child = child->next_sibling()) {
            if(!strcmp(child->name(), "net")) {
                NetConfigT net_config;
                for(xml_node<> *item = child->first_node(); item; item = item->next_sibling()) {
                    if(!strcmp(item->name(), "plane")) {
                        PlaneConfigT plane_config;
                        for(xml_attribute<> *attr = item->first_attribute(); attr; attr = attr->next_attribute()) {
                            if(!strcmp(attr->name(), "id")) {
                                plane_config.id = lexical_cast<IdT>(attr->value());
                            }
                            if(!strcmp(attr->name(), "input")) {
                                plane_config.is_input = (!strcmp(attr->value(), "true"));
                            }
                            if(!strcmp(attr->name(), "width")) {
                                plane_config.width = lexical_cast<unsigned>(attr->value());
                            }
                            if(!strcmp(attr->name(), "height")) {
                                plane_config.height = lexical_cast<unsigned>(attr->value());
                            }
                            if(!strcmp(attr->name(), "window_width")) {
                                plane_config.window_width = lexical_cast<unsigned>(attr->value());
                            }
                            if(!strcmp(attr->name(), "window_height")) {
                                plane_config.window_height = lexical_cast<unsigned>(attr->value());
                            }
                        }
                        net_config.planes.push_back(plane_config);
                    }
                    if(!strcmp(item->name(), "connection")) {
                        ConnectionConfigT connection_config;
                        for(xml_attribute<> *attr = item->first_attribute(); attr; attr = attr->next_attribute()) {
                            if(!strcmp(attr->name(), "from")) {
                                connection_config.from = lexical_cast<IdT>(attr->value());
                            }
                            if(!strcmp(attr->name(), "to")) {
                                connection_config.to = lexical_cast<IdT>(attr->value());
                            }
                            if(!strcmp(attr->name(), "density")) {
                                connection_config.density = lexical_cast<Float>(attr->value());
                            }
                        }
                        net_config.connections.push_back(connection_config);
                    }
                }
                config.nets.push_back(net_config);
            }
            if(!strcmp(child->name(), "weight_randomization")) {
                for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                    if(!strcmp(attr->name(), "min")) {
                        config.weight_randomization.min = lexical_cast<Float>(attr->value());
                    }
                    if(!strcmp(attr->name(), "max")) {
                        config.weight_randomization.max = lexical_cast<Float>(attr->value());
                    }
                }
            }
            if(!strcmp(child->name(), "lms")) {
                for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                    if(!strcmp(attr->name(), "learning_rate")) {
                        config.lms.learning_rate = lexical_cast<Float>(attr->value());
                    }
                    if(!strcmp(attr->name(), "annealing_tsc")) {
                        config.lms.annealing_tsc = lexical_cast<unsigned>(attr->value());
                    }
                    if(!strcmp(attr->name(), "epochs")) {
                        config.lms.epochs = lexical_cast<unsigned>(attr->value());
                    }
                }
            }
            if(!strcmp(child->name(), "faces")) {
                for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                    if(!strcmp(attr->name(), "database")) {
                        config.faces.database_path.append(attr->value());
                    }
                    if(!strcmp(attr->name(), "seed")) {
                        config.faces.random_seed = lexical_cast<unsigned>(attr->value());
                    }
                    if(!strcmp(attr->name(), "men")) {
                        config.faces.men = lexical_cast<unsigned>(attr->value());
                    }
                    if(!strcmp(attr->name(), "train_percent")) {
                        config.faces.train_percent = lexical_cast<Float>(attr->value());
                    }
                    if(!strcmp(attr->name(), "report_frequency")) {
                        config.faces.report_frequency = lexical_cast<unsigned>(attr->value());
                    }
                    if(!strcmp(attr->name(), "stop_error")) {
                        config.faces.stop_error = lexical_cast<Float>(attr->value());
                    }
                }
            }
        }

    } catch (exception e){
        cout<<e.what();
    };

    config.print();
};
