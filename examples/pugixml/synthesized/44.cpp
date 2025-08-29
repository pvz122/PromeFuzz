// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13443:36 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13443:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13449:36 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13449:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13443:36 in pugixml.hpp
// pugi::xml_node::select_node at pugixml.cpp:13443:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
// pugi::xpath_node::node at pugixml.cpp:12725:36 in pugixml.hpp
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root();
    if (!root) return 0;

    pugi::xpath_node xpath_node1 = root.select_node("//node");
    pugi::xpath_node xpath_node2 = root.select_node("//node");

    pugi::xml_node node1 = xpath_node1.node();
    pugi::xml_node node2 = xpath_node2.node();

    pugi::xpath_query query("//node");
    pugi::xpath_node xpath_node3 = root.select_node(query);
    pugi::xpath_node xpath_node4 = root.select_node(query);

    pugi::xml_node node3 = xpath_node3.node();
    pugi::xml_node node4 = xpath_node4.node();

    pugi::xpath_node xpath_node5 = root.select_node("//node");
    pugi::xpath_node xpath_node6 = root.select_node("//node");

    pugi::xml_node node5 = xpath_node5.node();
    pugi::xml_node node6 = xpath_node6.node();

    return 0;
}