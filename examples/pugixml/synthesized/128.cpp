// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::reset at pugixml.cpp:7487:34 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace_own at pugixml.cpp:7760:46 in pugixml.hpp
// pugi::xml_document::load at pugixml.cpp:7694:46 in pugixml.hpp
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
#include <cstring>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    if (Size > 0) {
        char* str = new char[Size + 1];
        std::memcpy(str, Data, Size);
        str[Size] = '\0';
        doc.load_string(str);
        delete[] str;
    }

    // Test reset
    doc.reset();

    // Test load_file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    if (outfile.is_open()) {
        outfile.write(reinterpret_cast<const char*>(Data), Size);
        outfile.close();
        doc.load_file("./dummy_file");
    }

    // Test load_buffer_inplace
    if (Size > 0) {
        void* buffer = std::malloc(Size);
        std::memcpy(buffer, Data, Size);
        doc.load_buffer_inplace(buffer, Size);
        std::free(buffer);
    }

    // Test load_buffer_inplace_own
    if (Size > 0) {
        void* buffer = std::malloc(Size);
        std::memcpy(buffer, Data, Size);
        doc.load_buffer_inplace_own(buffer, Size);
    }

    // Test load
    if (Size > 0) {
        std::stringstream stream;
        stream.write(reinterpret_cast<const char*>(Data), Size);
        doc.load(stream);
    }

    return 0;
}