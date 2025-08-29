// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_attribute::next_attribute at pugixml.cpp:5286:44 in pugixml.hpp
// pugi::xml_attribute::next_attribute at pugixml.cpp:5286:44 in pugixml.hpp
// pugi::xml_attribute::previous_attribute at pugixml.cpp:5292:44 in pugixml.hpp
// pugi::xml_attribute::previous_attribute at pugixml.cpp:5292:44 in pugixml.hpp
// pugi::xml_attribute::next_attribute at pugixml.cpp:5286:44 in pugixml.hpp
// pugi::xml_attribute::previous_attribute at pugixml.cpp:5292:44 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root();
    if (!root) return 0;

    std::string_view childName = "child";
    std::string_view attrName = "attr";

    pugi::xml_node childNode = root.child(childName.data());
    pugi::xml_attribute attr = childNode.attribute(attrName.data());
    pugi::xml_node childNode2 = root.child(childName.data());
    pugi::xml_attribute attr2 = childNode2.attribute(attrName.data());

    if (attr) {
        pugi::xml_attribute nextAttr = attr.next_attribute();
        pugi::xml_attribute nextAttr2 = nextAttr.next_attribute();
        pugi::xml_attribute prevAttr = nextAttr2.previous_attribute();
        pugi::xml_attribute prevAttr2 = prevAttr.previous_attribute();
        pugi::xml_attribute nextAttr3 = prevAttr2.next_attribute();
        pugi::xml_attribute prevAttr3 = nextAttr3.previous_attribute();
    }

    return 0;
}