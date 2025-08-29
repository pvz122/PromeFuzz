// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::load at pugixml.cpp:7694:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace_own at pugixml.cpp:7760:46 in pugixml.hpp
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
#include <fstream>
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    {
        std::vector<char> buffer(Data, Data + Size);
        buffer.push_back('\0'); // Ensure null-termination
        doc.load_string(buffer.data());
    }

    // Test load_buffer_inplace
    {
        std::vector<char> buffer(Data, Data + Size);
        doc.load_buffer_inplace(buffer.data(), buffer.size());
    }

    // Test load_buffer
    {
        std::vector<char> buffer(Data, Data + Size);
        doc.load_buffer(buffer.data(), buffer.size());
    }

    // Test load
    {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        std::ifstream inFile("./dummy_file", std::ios::binary);
        doc.load(inFile);
    }

    // Test load_buffer_inplace_own
    {
        std::vector<char> buffer(Data, Data + Size);
        void* buf = malloc(buffer.size());
        if (buf) {
            memcpy(buf, buffer.data(), buffer.size());
            doc.load_buffer_inplace_own(buf, buffer.size());
        }
    }

    // Test load_file
    {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        doc.load_file("./dummy_file");
    }

    return 0;
}