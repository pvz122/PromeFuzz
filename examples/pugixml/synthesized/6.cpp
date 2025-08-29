// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xpath_variable::get_node_set at pugixml.cpp:12971:53 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12984:36 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12976:36 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12992:36 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13454:40 in pugixml.hpp
// pugi::xpath_variable::get_boolean at pugixml.cpp:12955:36 in pugixml.hpp
// pugi::xpath_variable::get_number at pugixml.cpp:12960:38 in pugixml.hpp
// pugi::xpath_variable::get_string at pugixml.cpp:12965:45 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) {
        return 0;
    }

    pugi::xml_node node = doc.first_child();
    pugi::xpath_variable_set vars;
    pugi::xpath_variable* var = vars.add("var", pugi::xpath_type_node_set);

    var->get_node_set();
    var->set(42.0);
    var->set(true);
    var->set("fuzz_string");

    node.select_nodes("//node", &vars);
    var->get_boolean();
    var->get_number();
    var->get_string();
    node.first_child();

    return 0;
}