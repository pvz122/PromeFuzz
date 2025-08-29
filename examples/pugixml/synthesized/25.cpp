// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child_value at pugixml.cpp:5925:39 in pugixml.hpp
// pugi::xml_node::child_value at pugixml.cpp:5943:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
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
    pugi::xml_node child3 = child2.child("child3");
    if (!child3) return 0;
    pugi::xml_node child4 = child3.child("child4");
    if (!child4) return 0;
    pugi::xml_node child5 = child4.child("child5");
    if (!child5) return 0;
    pugi::xml_node child6 = child5.child("child6");
    if (!child6) return 0;
    pugi::xml_node child7 = child6.child("child7");
    if (!child7) return 0;

    pugi::xml_text text = child7.text();
    pugi::xml_node child8 = child7.child("child8");
    if (child8) {
        const char* value1 = child8.child_value();
        const char* value2 = child8.child_value("child9");
    }

    return 0;
}