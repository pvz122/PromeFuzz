// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_text::as_ullong at pugixml.cpp:7028:44 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7116:30 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7052:30 in pugixml.hpp
// pugi::xml_text::as_uint at pugixml.cpp:6987:38 in pugixml.hpp
// pugi::xml_text::as_bool at pugixml.cpp:7011:30 in pugixml.hpp
// pugi::xml_text::empty at pugixml.cpp:6958:30 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_text text;

    // Test as_ullong
    text.as_ullong();

    // Test set
    text.set(true);
    std::string_view sv(reinterpret_cast<const char*>(Data), Size);
    text.set(sv);

    // Test as_uint
    text.as_uint();

    // Test as_bool
    text.as_bool();

    // Test empty
    text.empty();

    return 0;
}