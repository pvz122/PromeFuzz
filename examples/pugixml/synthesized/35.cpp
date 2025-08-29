// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5863:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5863:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5863:39 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5471:35 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5471:35 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5471:35 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.first_child();
    if (!root) return 0;

    pugi::xml_node firstChild = root.first_child();
    if (!firstChild) return 0;

    std::string_view attrName1(reinterpret_cast<const char*>(Data), Size % 256);
    std::string_view attrName2(reinterpret_cast<const char*>(Data + Size % 256), Size % 256);
    std::string_view attrName3(reinterpret_cast<const char*>(Data + (Size % 256) * 2), Size % 256);

    pugi::xml_attribute attr1 = firstChild.attribute(attrName1.data());
    pugi::xml_attribute attr2 = firstChild.attribute(attrName2.data());
    pugi::xml_attribute attr3 = firstChild.attribute(attrName3.data());

    pugi::xml_attribute hint;
    pugi::xml_attribute attr4 = firstChild.attribute(attrName1, hint);
    pugi::xml_attribute attr5 = firstChild.attribute(attrName2, hint);
    pugi::xml_attribute attr6 = firstChild.attribute(attrName3, hint);

    if (attr1) attr1.set_name(attrName1);
    if (attr2) attr2.set_name(attrName2);
    if (attr3) attr3.set_name(attrName3);

    pugi::xml_attribute attr7 = firstChild.attribute(attrName1.data());
    pugi::xml_attribute attr8 = firstChild.attribute(attrName2.data());
    pugi::xml_attribute attr9 = firstChild.attribute(attrName3.data());

    return 0;
}