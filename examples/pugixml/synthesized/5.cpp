// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13454:40 in pugixml.hpp
// pugi::xpath_node_set::type at pugixml.cpp:12869:54 in pugixml.hpp
// pugi::xpath_node_set::sort at pugixml.cpp:12900:36 in pugixml.hpp
// pugi::xpath_node_set::empty at pugixml.cpp:12879:36 in pugixml.hpp
// pugi::xpath_node_set::empty at pugixml.cpp:12879:36 in pugixml.hpp
// pugi::xpath_node::attribute at pugixml.cpp:12730:41 in pugixml.hpp
// pugi::xpath_node::parent at pugixml.cpp:12735:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xpath_node_set node_set = doc.select_nodes("//*");
    pugi::xpath_node_set::type_t type = node_set.type();
    node_set.sort();
    bool is_empty = node_set.empty();

    if (!node_set.empty()) {
        pugi::xpath_node xpath_node = node_set[0];
        pugi::xml_attribute attr = xpath_node.attribute();
        pugi::xml_node parent = xpath_node.parent();
        pugi::xml_node node = xpath_node.node();
        pugi::xml_node root = node.root();
    }

    return 0;
}