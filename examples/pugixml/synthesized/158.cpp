// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::reset at pugixml.cpp:7493:34 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7736:46 in pugixml.hpp
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;

    // Fuzz load_string
    {
        char* nullTerminatedData = new char[Size + 1];
        std::memcpy(nullTerminatedData, Data, Size);
        nullTerminatedData[Size] = '\0';
        doc.load_string(nullTerminatedData);
        delete[] nullTerminatedData;
    }

    // Fuzz load_buffer
    doc.load_buffer(Data, Size);

    // Fuzz reset
    pugi::xml_document proto;
    proto.reset(doc);

    // Fuzz save_file
    doc.save_file("./dummy_file");

    // Fuzz load_file
    {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();
        doc.load_file(L"./dummy_file", rand(), static_cast<pugi::xml_encoding>(rand() % 10));
    }

    // Fuzz load (std::istream)
    {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();
        std::ifstream inFile("./dummy_file", std::ios::binary);
        doc.load(inFile);
    }

    return 0;
}