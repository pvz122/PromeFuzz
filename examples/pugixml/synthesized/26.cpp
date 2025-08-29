// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::append_buffer at pugixml.cpp:6625:42 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::remove_children at pugixml.cpp:6604:30 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::append_buffer at pugixml.cpp:6625:42 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    pugi::xml_node child1 = root.append_child(pugi::node_element);
    pugi::xml_node child2 = root.append_child("child");

    pugi::xml_node found_child1 = root.child("child");
    pugi::xml_parse_result result = root.append_buffer(Data, Size);

    pugi::xml_node found_child2 = root.child("child");
    pugi::xml_node found_child3 = root.child("child");

    root.remove_children();

    pugi::xml_node found_child4 = root.child("child");

    result = root.append_buffer(Data, Size);

    pugi::xml_node found_child5 = root.child("child");

    return 0;
}