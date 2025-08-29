// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5640:67 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5640:67 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5640:67 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5640:67 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::begin at pugixml.hpp:337:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_object_range::begin at pugixml.hpp:337:6 in pugixml.hpp
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
#include <cstddef>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root();
    if (!root) return 0;

    pugi::xml_node node1 = root.child("node1");
    pugi::xml_node node2 = node1.child("node2");
    pugi::xml_node node3 = node2.child("node3");
    pugi::xml_node node4 = node3.child("node4");
    pugi::xml_node node5 = node4.child("node5");
    pugi::xml_node node6 = node5.child("node6");
    pugi::xml_node node7 = node6.child("node7");
    pugi::xml_node node8 = node7.child("node8");

    pugi::xml_object_range<pugi::xml_named_node_iterator> range1 = node8.children("child1");
    pugi::xml_object_range<pugi::xml_named_node_iterator> range2 = node8.children("child2");
    pugi::xml_object_range<pugi::xml_named_node_iterator> range3 = node8.children("child3");
    pugi::xml_object_range<pugi::xml_named_node_iterator> range4 = node8.children("child4");

    pugi::xml_node first_child = node8.first_child();
    pugi::xml_node last_child = node8.last_child();

    (void)range1.end();
    (void)range2.end();
    (void)range3.end();
    (void)range4.end();

    (void)first_child;
    (void)last_child;

    (void)range1.end();
    (void)range2.end();
    (void)range3.end();
    (void)range4.end();

    (void)range1.end();
    (void)range2.end();
    (void)range3.end();
    (void)range4.end();

    (void)range1.begin();
    (void)range2.end();
    (void)range3.end();
    (void)range4.begin();

    return 0;
}