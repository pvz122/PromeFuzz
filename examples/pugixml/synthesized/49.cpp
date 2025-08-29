// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6180:39 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;
    char* buffer = new char[Size];
    std::memcpy(buffer, Data, Size);

    pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, Size);
    if (!result) {
        delete[] buffer;
        return 0;
    }

    pugi::xml_node root = doc.root();
    pugi::xml_node child1 = root.append_child("child1");
    pugi::xml_node child2 = root.append_child("child2");

    pugi::xml_attribute attr1 = child1.append_attribute("attr1");
    pugi::xml_attribute attr2 = child2.append_attribute("attr2");

    pugi::xml_node firstChild = root.first_child();
    pugi::xml_attribute firstAttr = firstChild.first_attribute();

    pugi::xml_node copiedChild = root.append_copy(child1);
    pugi::xml_attribute copiedAttr = copiedChild.append_copy(attr1);

    pugi::xml_node anotherChild = root.append_child("anotherChild");
    pugi::xml_attribute anotherAttr = anotherChild.append_attribute("anotherAttr");

    pugi::xml_attribute firstAttrAgain = anotherChild.first_attribute();

    delete[] buffer;
    return 0;
}