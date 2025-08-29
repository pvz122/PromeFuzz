// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::begin at pugixml.cpp:5615:44 in pugixml.hpp
// pugi::xml_node::end at pugixml.cpp:5620:44 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
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
#include <stdint.h>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root();
    if (!root) return 0;

    // Test begin()
    auto it = root.begin();
    if (it != root.end()) {
        // Test append_copy()
        pugi::xml_node copied_node = root.append_copy(*it);
        if (!copied_node) return 0;

        // Test remove_child()
        root.remove_child(copied_node);
    }

    // Test append_child()
    pugi::xml_node new_child = root.append_child(pugi::node_element);
    if (!new_child) return 0;

    // Test last_child()
    pugi::xml_node last_child = root.last_child();
    if (!last_child) return 0;

    // Test traverse()
    class SimpleWalker : public pugi::xml_tree_walker {
    public:
        virtual bool for_each(pugi::xml_node& node) {
            return true;
        }
    };

    SimpleWalker walker;
    root.traverse(walker);

    return 0;
}