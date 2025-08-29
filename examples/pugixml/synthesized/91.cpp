// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::set_name at pugixml.cpp:5974:30 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5456:35 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5984:30 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5974:30 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5463:35 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5456:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5516:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5523:35 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(long)) return 0;

    pugi::xml_node node;
    pugi::xml_attribute attr;

    // Initialize node and attribute with dummy data
    node.set_name("dummy_node");
    attr.set_name("dummy_attr");

    // Fuzz pugi::xml_node::set_name
    std::string_view node_name(reinterpret_cast<const char*>(Data), Size);
    node.set_name(node_name.data(), node_name.size());
    node.set_name(node_name.data());

    // Fuzz pugi::xml_attribute::set_name
    std::string_view attr_name(reinterpret_cast<const char*>(Data), Size);
    attr.set_name(attr_name.data(), attr_name.size());
    attr.set_name(attr_name.data());

    // Fuzz pugi::xml_attribute::set_value
    long long_value;
    unsigned long ulong_value;
    std::memcpy(&long_value, Data, sizeof(long));
    std::memcpy(&ulong_value, Data, sizeof(unsigned long));
    attr.set_value(long_value);
    attr.set_value(ulong_value);

    return 0;
}