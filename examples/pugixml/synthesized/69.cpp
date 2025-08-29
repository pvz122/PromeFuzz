// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::as_wide at pugixml.cpp:7851:59 in pugixml.hpp
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
#include <fstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a dummy file
    const char* file_path = "./dummy_file";
    std::ofstream file(file_path, std::ios::binary);
    if (!file.is_open()) return 0;
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();

    // Load the XML document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_path);
    if (!result) return 0;

    // Test pugi::xml_document::save_file
    doc.save_file(file_path);
    doc.save_file(pugi::as_wide(file_path).c_str());

    // Test pugi::as_wide
    std::string narrow_str(reinterpret_cast<const char*>(Data), Size);
    pugi::as_wide(narrow_str.c_str());
    pugi::as_wide(narrow_str);

    // Test pugi::as_utf8
    std::wstring wide_str(reinterpret_cast<const wchar_t*>(Data), Size / sizeof(wchar_t));
    pugi::as_utf8(wide_str.c_str());
    pugi::as_utf8(wide_str);

    // Clean up
    std::remove(file_path);

    return 0;
}