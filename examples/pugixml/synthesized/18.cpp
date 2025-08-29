// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13454:40 in pugixml.hpp
// pugi::xpath_node_set::size at pugixml.cpp:12874:38 in pugixml.hpp
// pugi::xpath_node_set::type at pugixml.cpp:12869:54 in pugixml.hpp
// pugi::xpath_node_set::empty at pugixml.cpp:12879:36 in pugixml.hpp
// pugi::xpath_node_set::first at pugixml.cpp:12905:42 in pugixml.hpp
// pugi::xpath_node_set::end at pugixml.cpp:12895:62 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    const char* xpath_query = "//*";
    pugi::xpath_node_set nodes = root.select_nodes(xpath_query);

    nodes.size();
    nodes.type();
    nodes.empty();
    nodes.first();
    nodes.end();

    return 0;
}