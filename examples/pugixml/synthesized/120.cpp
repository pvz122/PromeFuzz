// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::reset at pugixml.cpp:7487:34 in pugixml.hpp
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
#include <fstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;

    // Load from buffer
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    // Save to file
    doc.save_file("./dummy_file");

    // Load from file
    result = doc.load_file("./dummy_file");
    if (!result) return 0;

    // Load from string (create null-terminated copy)
    char* nullTerminatedData = new char[Size + 1];
    std::memcpy(nullTerminatedData, Data, Size);
    nullTerminatedData[Size] = '\0';
    result = doc.load_string(nullTerminatedData);
    delete[] nullTerminatedData;
    if (!result) return 0;

    // Reset document
    doc.reset();

    return 0;
}