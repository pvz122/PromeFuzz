// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::value at pugixml.cpp:5697:39 in pugixml.hpp
// pugi::xml_node::set_value at pugixml.cpp:6006:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::parent at pugixml.cpp:5910:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::set_memory_management_functions at pugixml.cpp:7864:37 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.first_child();
    pugi::xml_node child = root.first_child();
    pugi::xml_node sibling = child.next_sibling();
    const char* value = child.value();
    child.set_value("new_value");
    pugi::xml_node first_child = root.first_child();
    pugi::xml_node next_sibling = first_child.next_sibling();
    pugi::xml_node next_sibling2 = next_sibling.next_sibling();
    pugi::xml_node parent = next_sibling2.parent();
    parent.remove_child(first_child);

    auto allocate = [](size_t size) -> void* { return malloc(size); };
    auto deallocate = [](void* ptr) { free(ptr); };
    pugi::set_memory_management_functions(allocate, deallocate);

    return 0;
}