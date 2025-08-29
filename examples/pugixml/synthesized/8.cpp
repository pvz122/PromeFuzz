// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5974:30 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5456:35 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7037:30 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;
    std::string xml_string(reinterpret_cast<const char*>(Data), Size);
    pugi::xml_parse_result result = doc.load_string(xml_string.c_str());

    if (!result) return 0;

    pugi::xml_node root = doc.child("root");
    if (!root) return 0;

    pugi::xml_node child1 = root.child("child1");
    if (!child1) return 0;

    pugi::xml_node child2 = child1.child("child2");
    if (!child2) return 0;

    child2.set_name("new_child2");

    pugi::xml_attribute attr1 = child2.attribute("attr1");
    if (!attr1) return 0;

    attr1.set_name("new_attr1");

    pugi::xml_attribute attr2 = child2.attribute("attr2");
    if (!attr2) return 0;

    attr2.set_value("new_value");

    pugi::xml_node child3 = child2.child("child3");
    if (!child3) return 0;

    pugi::xml_text text = child3.text();
    text.set("new_text");

    pugi::xml_node copied_node = child3.append_copy(child2);
    if (!copied_node) return 0;

    pugi::xml_node child4 = copied_node.child("child4");
    if (!child4) return 0;

    pugi::xml_node copied_node2 = child4.append_copy(child3);
    if (!copied_node2) return 0;

    return 0;
}