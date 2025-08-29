// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::begin at pugixml.cpp:5615:44 in pugixml.hpp
// pugi::xml_node::end at pugixml.cpp:5620:44 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
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
#include <pugixml.hpp>
#include <cstdint>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    // Test pugi::xml_node::begin
    auto it = root.begin();
    if (it != root.end()) {
        // Test pugi::xml_node::append_copy
        pugi::xml_node copied_node = root.append_copy(*it);
        if (copied_node) {
            // Test pugi::xml_node::remove_child
            root.remove_child(copied_node);
        }
    }

    // Test pugi::xml_node::append_child
    pugi::xml_node new_child = root.append_child(pugi::node_element);
    if (new_child) {
        // Test pugi::xml_node::last_child
        pugi::xml_node last_child = root.last_child();
        if (last_child) {
            // Test pugi::xml_node::remove_child
            root.remove_child(last_child);
        }
    }

    // Test pugi::xml_node::traverse
    class SimpleWalker : public pugi::xml_tree_walker {
    public:
        bool for_each(pugi::xml_node& node) override {
            return true;
        }
    };
    SimpleWalker walker;
    root.traverse(walker);

    return 0;
}