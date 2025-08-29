// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    std::vector<char> buffer(Size + 1);
    std::copy(Data, Data + Size, buffer.begin());
    buffer[Size] = '\0';
    doc.load_string(buffer.data());

    // Test load_file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();
    doc.load_file("./dummy_file");

    // Test load_buffer
    doc.load_buffer(Data, Size);

    // Test load_buffer_inplace
    void* inplace_buffer = malloc(Size);
    if (inplace_buffer) {
        std::memcpy(inplace_buffer, Data, Size);
        doc.load_buffer_inplace(inplace_buffer, Size);
        free(inplace_buffer);
    }

    // Test load_buffer_inplace_own
    void* inplace_own_buffer = malloc(Size);
    if (inplace_own_buffer) {
        std::memcpy(inplace_own_buffer, Data, Size);
        doc.load_buffer_inplace_own(inplace_own_buffer, Size);
    }

    // Test load
    std::istringstream iss(std::string(reinterpret_cast<const char*>(Data), Size));
    doc.load(iss);

    return 0;
}