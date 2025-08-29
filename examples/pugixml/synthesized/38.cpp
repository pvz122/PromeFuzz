// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6329:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6329:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6329:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6329:34 in pugixml.hpp
// pugi::xml_node::prepend_child at pugixml.cpp:6329:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    std::string name(reinterpret_cast<const char*>(Data), Size);

    root.prepend_child(name.c_str());
    root.child(name.c_str());
    root.prepend_child(name.c_str());
    root.child(name.c_str());
    root.child(name.c_str());
    root.prepend_child(name.c_str());
    root.child(name.c_str());
    root.prepend_child(name.c_str());
    root.prepend_child(name.c_str());

    return 0;
}