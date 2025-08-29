// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace_own at pugixml.cpp:7760:46 in pugixml.hpp
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_buffer
    doc.load_buffer(Data, Size);

    // Test load_buffer_inplace
    char* buffer_inplace = (char*)malloc(Size);
    if (buffer_inplace) {
        memcpy(buffer_inplace, Data, Size);
        doc.load_buffer_inplace(buffer_inplace, Size);
        free(buffer_inplace);
    }

    // Test load_buffer_inplace_own
    char* buffer_inplace_own = (char*)malloc(Size);
    if (buffer_inplace_own) {
        memcpy(buffer_inplace_own, Data, Size);
        doc.load_buffer_inplace_own(buffer_inplace_own, Size);
    }

    // Test load_string
    char* buffer_string = (char*)malloc(Size + 1);
    if (buffer_string) {
        memcpy(buffer_string, Data, Size);
        buffer_string[Size] = '\0';
        doc.load_string(buffer_string);
        free(buffer_string);
    }

    // Test load_file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    if (outfile.is_open()) {
        outfile.write((const char*)Data, Size);
        outfile.close();
        doc.load_file("./dummy_file");
    }

    return 0;
}