// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::find_node at pugixml.hpp:707:42 in pugixml.hpp
// pugi::xml_node::find_child at pugixml.hpp:695:42 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::traverse at pugixml.cpp:6786:30 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child(pugi::node_element);

    // Append child nodes
    for (size_t i = 0; i < Size; ++i) {
        root.append_child(pugi::node_element);
    }

    // Find node using predicate
    root.find_node([](pugi::xml_node) { return true; });

    // Find child node using predicate
    root.find_child([](pugi::xml_node) { return true; });

    // Get last child
    pugi::xml_node lastChild = root.last_child();

    // Get first child
    pugi::xml_node firstChild = root.first_child();

    // Traverse the tree
    struct SimpleWalker : pugi::xml_tree_walker {
        bool for_each(pugi::xml_node& node) override {
            return true;
        }
    };

    SimpleWalker walker;
    root.traverse(walker);

    return 0;
}