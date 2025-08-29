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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;

    // Fuzz load_string
    {
        std::vector<char> buffer(Data, Data + Size);
        buffer.push_back('\0');
        doc.load_string(buffer.data());
    }

    // Fuzz reset
    doc.reset();

    // Fuzz load_file
    {
        std::ofstream file("dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();
        doc.load_file("dummy_file");
    }

    // Fuzz load_buffer_inplace
    {
        std::vector<char> buffer(Data, Data + Size);
        doc.load_buffer_inplace(buffer.data(), buffer.size());
    }

    // Fuzz load_buffer_inplace_own
    {
        void* buffer = malloc(Size);
        if (buffer) {
            memcpy(buffer, Data, Size);
            doc.load_buffer_inplace_own(buffer, Size);
        }
    }

    // Fuzz load
    {
        std::ofstream file("dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();
        std::ifstream stream("dummy_file", std::ios::binary);
        doc.load(stream);
    }

    return 0;
}