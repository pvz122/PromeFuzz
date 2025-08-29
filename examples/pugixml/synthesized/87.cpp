// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6072:39 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6180:39 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6055:39 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6232:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5823:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_before at pugixml.cpp:6090:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("root");

    // Ensure the name is null-terminated
    std::vector<char> name(Size + 1);
    std::memcpy(name.data(), Data, Size);
    name[Size] = '\0';

    // Test insert_attribute_after
    pugi::xml_attribute attr1 = node.append_attribute("attr1");
    pugi::xml_attribute attr2 = node.insert_attribute_after(name.data(), attr1);

    // Test append_copy
    pugi::xml_attribute attr3 = node.append_copy(attr1);

    // Test prepend_attribute
    pugi::xml_attribute attr4 = node.prepend_attribute(name.data());

    // Test insert_copy_before
    pugi::xml_attribute attr5 = node.insert_copy_before(attr1, attr2);

    // Test attribute
    pugi::xml_attribute hint;
    pugi::xml_attribute attr6 = node.attribute(name.data(), hint);

    // Test insert_attribute_before
    pugi::xml_attribute attr7 = node.insert_attribute_before(name.data(), attr1);

    return 0;
}