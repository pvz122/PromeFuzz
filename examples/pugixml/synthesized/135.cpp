// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::get_memory_allocation_function at pugixml.cpp:7870:52 in pugixml.hpp
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
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    {
        char* nullTerminatedData = new char[Size + 1];
        std::memcpy(nullTerminatedData, Data, Size);
        nullTerminatedData[Size] = '\0';
        doc.load_string(nullTerminatedData);
        delete[] nullTerminatedData;
    }

    // Test load_file
    {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();
        doc.load_file("./dummy_file");
    }

    // Test load_buffer
    doc.load_buffer(Data, Size);

    // Test load_buffer_inplace
    {
        char* inplaceData = new char[Size];
        std::memcpy(inplaceData, Data, Size);
        doc.load_buffer_inplace(inplaceData, Size);
        delete[] inplaceData;
    }

    // Test load_buffer_inplace_own
    {
        void* ownedData = pugi::get_memory_allocation_function()(Size);
        std::memcpy(ownedData, Data, Size);
        doc.load_buffer_inplace_own(ownedData, Size);
    }

    // Test load (std::istream)
    {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();
        std::ifstream inFile("./dummy_file", std::ios::binary);
        doc.load(inFile);
    }

    return 0;
}