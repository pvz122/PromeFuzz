// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::begin at pugixml.cpp:5615:44 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
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
#include <cstdint>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child(pugi::node_element);
    pugi::xml_node child1 = root.append_child(pugi::node_element);
    pugi::xml_node child2 = root.append_child(pugi::node_element);

    // Test pugi::xml_node::begin
    auto it = root.begin();

    // Test pugi::xml_node::append_copy
    pugi::xml_node copied_node = root.append_copy(child1);

    // Test pugi::xml_node::append_child
    pugi::xml_node new_child = root.append_child(pugi::node_element);

    // Test pugi::xml_node::remove_child
    bool removed = root.remove_child(child2);

    // Test pugi::xml_node::last_child
    pugi::xml_node last_child = root.last_child();

    // Test pugi::xml_node::traverse
    struct TestWalker : pugi::xml_tree_walker {
        bool for_each(pugi::xml_node& node) override {
            return true;
        }
    };
    TestWalker walker;
    root.traverse(walker);

    return 0;
}