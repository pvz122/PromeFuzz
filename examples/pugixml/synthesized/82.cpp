// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6143:39 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6180:39 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6232:39 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6055:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_before at pugixml.cpp:6161:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr1 = node.append_attribute("attr1");
    pugi::xml_attribute attr2 = node.append_attribute("attr2");

    // Ensure the name is null-terminated
    std::vector<char> name_vec(Data, Data + Size);
    name_vec.push_back('\0');
    std::string_view name(name_vec.data(), Size);

    // Test insert_attribute_after
    node.insert_attribute_after(name, attr1);

    // Test append_copy
    node.append_copy(attr1);

    // Test insert_copy_before
    node.insert_copy_before(attr1, attr2);

    // Test prepend_attribute
    node.prepend_attribute(name.data());

    // Test attribute
    node.attribute(name.data());

    // Test insert_attribute_before
    node.insert_attribute_before(name, attr1);

    return 0;
}