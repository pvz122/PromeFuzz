// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::get at pugixml.cpp:6963:39 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7052:30 in pugixml.hpp
// pugi::xml_text::data at pugixml.cpp:7209:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7037:30 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root();
    pugi::xml_node child = root.child("child");
    pugi::xml_text text = child.text();
    const char* text_content = text.get();

    std::string_view new_text = "new_text";
    text.set(new_text);

    pugi::xml_node data_node = text.data();
    text.set("another_text");

    pugi::xml_node last_child = root.last_child();

    return 0;
}