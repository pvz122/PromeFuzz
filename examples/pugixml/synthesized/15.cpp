// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6302:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6284:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6267:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child(pugi::node_element);

    pugi::xml_node child1 = root.append_child(pugi::node_element);
    pugi::xml_node firstChild1 = root.first_child();
    pugi::xml_node firstChild2 = root.first_child();
    pugi::xml_node child2 = root.insert_child_after(pugi::node_element, firstChild2);
    pugi::xml_node firstChild3 = root.first_child();
    pugi::xml_node child3 = root.insert_child_before(pugi::node_element, firstChild3);
    pugi::xml_node firstChild4 = root.first_child();
    pugi::xml_node child4 = root.prepend_child(pugi::node_element);

    return 0;
}