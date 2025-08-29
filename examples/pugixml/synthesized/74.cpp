// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13460:40 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:13013:36 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12976:36 in pugixml.hpp
// pugi::xpath_variable::type at pugixml.cpp:12950:48 in pugixml.hpp
// pugi::xpath_variable::get_boolean at pugixml.cpp:12955:36 in pugixml.hpp
// pugi::xpath_variable::get_node_set at pugixml.cpp:12971:53 in pugixml.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "pugixml.hpp"

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    pugi::xpath_variable_set vars;
    pugi::xpath_variable* var = vars.add("var", pugi::xpath_type_boolean);
    if (!var) return 0;

    pugi::xpath_query query("//node");
    pugi::xpath_node_set nodes = root.select_nodes(query);

    var->set(nodes);
    var->set((Size % 2) == 0);

    pugi::xpath_value_type var_type = var->type();
    bool bool_val = var->get_boolean();
    pugi::xpath_node_set node_set_val = var->get_node_set();

    return 0;
}