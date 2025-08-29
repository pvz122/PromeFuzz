// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6055:39 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6126:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6055:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5766:34 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6126:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5766:34 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6055:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5766:34 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6126:39 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("root");

    // Ensure the input data is null-terminated
    std::vector<char> buffer(Data, Data + Size);
    buffer.push_back('\0');

    std::string_view attr_name(buffer.data(), Size);

    node.prepend_attribute(attr_name.data());
    node.prepend_attribute(attr_name);

    node.child(attr_name.data());

    node.prepend_attribute(attr_name.data());

    node.child(attr_name);

    node.prepend_attribute(attr_name);

    node.child(attr_name.data());

    node.child(attr_name);

    node.prepend_attribute(attr_name.data());

    node.child(attr_name.data());

    node.child(attr_name);

    node.prepend_attribute(attr_name);

    return 0;
}