// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_text::as_string at pugixml.cpp:6971:39 in pugixml.hpp
// pugi::xml_text::as_int at pugixml.cpp:6979:29 in pugixml.hpp
// pugi::xml_text::as_uint at pugixml.cpp:6987:38 in pugixml.hpp
// pugi::xml_text::as_double at pugixml.cpp:6995:32 in pugixml.hpp
// pugi::xml_text::as_float at pugixml.cpp:7003:31 in pugixml.hpp
// pugi::xml_text::as_bool at pugixml.cpp:7011:30 in pugixml.hpp
// pugi::xml_text::as_llong at pugixml.cpp:7020:35 in pugixml.hpp
// pugi::xml_text::as_ullong at pugixml.cpp:7028:44 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_text text;
    text.as_string();
    text.as_int();
    text.as_uint();
    text.as_double();
    text.as_float();
    text.as_bool();
    text.as_llong();
    text.as_ullong();

    return 0;
}