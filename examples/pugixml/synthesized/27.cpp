// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::get_memory_allocation_function at pugixml.cpp:7870:52 in pugixml.hpp
// pugi::get_memory_deallocation_function at pugixml.cpp:7875:54 in pugixml.hpp
// pugi::set_memory_management_functions at pugixml.cpp:7864:37 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize memory management functions
    pugi::allocation_function allocate = pugi::get_memory_allocation_function();
    pugi::deallocation_function deallocate = pugi::get_memory_deallocation_function();
    pugi::set_memory_management_functions(allocate, deallocate);

    // Create a document and a root node
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child(pugi::node_element);

    // Append a child node
    pugi::xml_node child = root.append_child(pugi::node_element);

    // Get the first child node
    pugi::xml_node first_child = root.first_child();

    return 0;
}