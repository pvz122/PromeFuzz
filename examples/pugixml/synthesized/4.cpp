// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xpath_query::evaluate_boolean at pugixml.cpp:13285:33 in pugixml.hpp
// pugi::xpath_query::evaluate_number at pugixml.cpp:13306:35 in pugixml.hpp
// pugi::xpath_query::evaluate_string at pugixml.cpp:13328:37 in pugixml.hpp
// pugi::xpath_query::evaluate_node at pugixml.cpp:13402:39 in pugixml.hpp
// pugi::xpath_query::evaluate_node_set at pugixml.cpp:13380:43 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xpath_variable_set vars;
    vars.add("remote", pugi::xpath_type_boolean);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xpath_query query("//*", &vars);
    pugi::xpath_node node = doc.first_child();

    query.evaluate_boolean(node);
    query.evaluate_number(node);
    query.evaluate_string(node);
    query.evaluate_node(node);
    query.evaluate_node_set(node);

    return 0;
}