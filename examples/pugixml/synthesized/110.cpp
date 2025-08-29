// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::begin at pugixml.cpp:5615:44 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::traverse at pugixml.cpp:6786:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
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

static void fuzz_xml_node_operations(pugi::xml_node& node, const uint8_t* data, size_t size) {
    if (size < 1) return;

    // Use the first byte to determine the operation
    uint8_t operation = data[0];
    data++;
    size--;

    switch (operation % 6) {
        case 0: {
            // Test begin()
            auto it = node.begin();
            break;
        }
        case 1: {
            // Test append_copy()
            pugi::xml_node copy_node = node.append_copy(node);
            break;
        }
        case 2: {
            // Test append_child()
            pugi::xml_node new_child = node.append_child();
            break;
        }
        case 3: {
            // Test remove_child()
            pugi::xml_node child = node.first_child();
            if (child) {
                node.remove_child(child);
            }
            break;
        }
        case 4: {
            // Test last_child()
            pugi::xml_node last_child = node.last_child();
            break;
        }
        case 5: {
            // Test traverse()
            class SimpleWalker : public pugi::xml_tree_walker {
            public:
                bool for_each(pugi::xml_node& node) override {
                    return true;
                }
            };
            SimpleWalker walker;
            node.traverse(walker);
            break;
        }
    }
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t* data, size_t size) {
    pugi::xml_document doc;
    if (size < 1) return 0;

    // Use the first byte to determine the node type
    uint8_t node_type = data[0] % 9; // There are 9 node types in pugi::xml_node_type
    data++;
    size--;

    pugi::xml_node node = doc.append_child(static_cast<pugi::xml_node_type>(node_type));

    fuzz_xml_node_operations(node, data, size);

    return 0;
}