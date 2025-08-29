// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Load from buffer
    doc.load_buffer(Data, Size);

    // Load from string (create null-terminated copy)
    if (Size > 0) {
        char* str = new char[Size + 1];
        std::copy(Data, Data + Size, str);
        str[Size] = '\0';
        doc.load_string(str);
        delete[] str;
    }

    // Load from file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();
    doc.load_file("./dummy_file");

    // Save to file
    doc.save_file("./dummy_file");

    // Reset document
    doc.reset();

    return 0;
}