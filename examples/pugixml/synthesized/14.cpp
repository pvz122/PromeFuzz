// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5794:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5732:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5903:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5808:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5751:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5794:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5732:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5903:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5808:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5751:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5794:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5732:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5732:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5903:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5808:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5751:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5751:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root().first_child();
    if (!root) return 0;

    std::string_view sv("dummy");

    root.next_sibling();
    root.next_sibling(sv);
    root.next_sibling("dummy");

    root.previous_sibling();
    root.previous_sibling(sv);
    root.previous_sibling("dummy");

    root.child("child1");
    root.child("child2");
    root.child("child3");
    root.child("child4");
    root.child("child5");
    root.child("child6");

    root.next_sibling();
    root.next_sibling(sv);
    root.next_sibling("dummy");

    root.previous_sibling();
    root.previous_sibling(sv);
    root.previous_sibling("dummy");

    root.next_sibling();
    root.next_sibling(sv);
    root.next_sibling("dummy");
    root.next_sibling("dummy");

    root.previous_sibling();
    root.previous_sibling(sv);
    root.previous_sibling("dummy");
    root.previous_sibling("dummy");

    return 0;
}