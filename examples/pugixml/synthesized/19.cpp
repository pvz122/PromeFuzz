// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6532:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6544:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6538:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6532:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6544:30 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6544:30 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6544:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6532:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6532:30 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("root");
    pugi::xml_attribute attr1 = node.append_attribute("attr1");
    pugi::xml_attribute attr2 = node.append_attribute("attr2");
    pugi::xml_attribute attr3 = node.append_attribute("attr3");

    node.remove_attribute("attr1");
    node.remove_attribute(attr2);
    node.remove_attribute(std::string_view("attr3"));

    pugi::xml_node child1 = node.append_child("child1");
    pugi::xml_node child2 = node.append_child("child2");

    node.child("child1");
    node.child("child2");

    node.remove_attribute("attr1");
    node.remove_attribute(attr2);

    pugi::xml_attribute attr4 = node.attribute("attr1");
    node.remove_attribute(attr4);

    pugi::xml_attribute attr5 = node.attribute("attr2");
    node.remove_attribute(attr5);

    node.remove_attribute("attr1");
    node.remove_attribute("attr2");

    return 0;
}