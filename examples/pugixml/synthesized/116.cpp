// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::find_node at pugixml.hpp:707:42 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
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
#include <cstdint>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    // Test find_node
    auto pred_node = [](pugi::xml_node node) { return true; };
    root.find_node(pred_node);

    // Test append_child
    root.append_child(pugi::node_element);

    // Test find_child
    auto pred_child = [](pugi::xml_node node) { return true; };
    root.find_child(pred_child);

    // Test last_child
    root.last_child();

    // Test first_child
    root.first_child();

    // Test traverse
    class DummyWalker : public pugi::xml_tree_walker {
    public:
        virtual bool for_each(pugi::xml_node& node) override {
            return true;
        }
    };
    DummyWalker walker;
    root.traverse(walker);

    return 0;
}