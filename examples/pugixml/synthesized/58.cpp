// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7819:34 in pugixml.hpp
// pugi::as_wide at pugixml.cpp:7851:59 in pugixml.hpp
// pugi::as_wide at pugixml.cpp:7858:59 in pugixml.hpp
// pugi::as_utf8 at pugixml.cpp:7839:44 in pugixml.hpp
// pugi::as_utf8 at pugixml.cpp:7846:44 in pugixml.hpp
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
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;
    std::string input(reinterpret_cast<const char*>(Data), Size);
    doc.load_string(input.c_str());

    // Save to file using both overloads
    doc.save_file("./dummy_file");
    doc.save_file(L"./dummy_file");

    // Test as_wide with both overloads
    std::wstring wide_str = pugi::as_wide(input.c_str());
    std::wstring wide_str2 = pugi::as_wide(input);

    // Test as_utf8 with both overloads
    std::string utf8_str = pugi::as_utf8(wide_str.c_str());
    std::string utf8_str2 = pugi::as_utf8(wide_str);

    return 0;
}