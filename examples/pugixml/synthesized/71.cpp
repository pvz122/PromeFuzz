// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::select_single_node at pugixml.cpp:13465:36 in pugixml.hpp
// pugi::xpath_query::result at pugixml.cpp:13424:54 in pugixml.hpp
// pugi::xpath_parse_result::description at pugixml.cpp:12919:47 in pugixml.hpp
// pugi::xpath_query::result at pugixml.cpp:13424:54 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13454:40 in pugixml.hpp
// pugi::xpath_exception::result at pugixml.cpp:12707:58 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13443:36 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root();
    if (!root) return 0;

    pugi::xpath_variable_set variables;

    // Fuzz pugi::xml_node::select_single_node
    root.select_single_node("//node");

    // Fuzz pugi::xpath_parse_result::description
    pugi::xpath_query query("//node");
    query.result().description();

    // Fuzz pugi::xpath_query::result
    query.result();

    // Fuzz pugi::xml_node::select_nodes
    root.select_nodes("//node");

    // Fuzz pugi::xpath_exception::result
    try {
        std::string query_str(reinterpret_cast<const char*>(Data), Size);
        pugi::xpath_query invalid_query(query_str.c_str());
    } catch (const pugi::xpath_exception& e) {
        e.result();
    }

    // Fuzz pugi::xml_node::select_node
    root.select_node("//node");

    return 0;
}