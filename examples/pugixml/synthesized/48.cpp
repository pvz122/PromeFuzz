// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13454:40 in pugixml.hpp
// pugi::xpath_node_set::size at pugixml.cpp:12874:38 in pugixml.hpp
// pugi::xpath_node_set::type at pugixml.cpp:12869:54 in pugixml.hpp
// pugi::xpath_node_set::empty at pugixml.cpp:12879:36 in pugixml.hpp
// pugi::xpath_node_set::first at pugixml.cpp:12905:42 in pugixml.hpp
// pugi::xpath_node_set::begin at pugixml.cpp:12890:62 in pugixml.hpp
// pugi::xpath_node_set::begin at pugixml.cpp:12890:62 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xpath_node_set nodes = doc.select_nodes("//*");

    nodes.size();
    nodes.type();
    nodes.empty();
    nodes.first();
    nodes.begin();
    nodes.begin();

    return 0;
}