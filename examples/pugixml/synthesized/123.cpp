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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    
    // Load from null-terminated string
    if (Size > 0) {
        char* nullTerminatedData = new char[Size + 1];
        std::memcpy(nullTerminatedData, Data, Size);
        nullTerminatedData[Size] = '\0';
        doc.load_string(nullTerminatedData);
        delete[] nullTerminatedData;
    }

    // Load from file
    std::ofstream file("./dummy_file", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();
        doc.load_file("./dummy_file");
    }

    // Load from buffer
    doc.load_buffer(Data, Size);

    // Load from buffer in-place
    if (Size > 0) {
        void* inplaceData = malloc(Size);
        std::memcpy(inplaceData, Data, Size);
        doc.load_buffer_inplace(inplaceData, Size);
        free(inplaceData);
    }

    // Load from buffer in-place with ownership
    if (Size > 0) {
        void* inplaceOwnData = malloc(Size);
        std::memcpy(inplaceOwnData, Data, Size);
        doc.load_buffer_inplace_own(inplaceOwnData, Size);
    }

    // Load from stream
    if (Size > 0) {
        std::istringstream stream(std::string(reinterpret_cast<const char*>(Data), Size));
        doc.load(stream);
    }

    return 0;
}