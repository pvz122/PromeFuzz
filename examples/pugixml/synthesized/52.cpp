// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6366:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5794:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6375:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6384:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6357:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5808:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");
    pugi::xml_node child1 = root.append_child("child1");
    pugi::xml_node child2 = root.append_child("child2");

    std::string_view name(reinterpret_cast<const char*>(Data), Size);

    root.prepend_child(name);
    child1.next_sibling(name);
    root.insert_child_after(name, child1);
    root.insert_child_before(name, child2);
    root.append_child(name);
    child2.previous_sibling(name);

    return 0;
}