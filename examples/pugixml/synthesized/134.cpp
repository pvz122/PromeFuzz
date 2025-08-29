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
#include <sstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    {
        std::string input(reinterpret_cast<const char*>(Data), Size);
        doc.load_string(input.c_str());
    }

    // Test reset
    doc.reset();

    // Test load_file
    {
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();
        doc.load_file("./dummy_file");
    }

    // Test load_buffer_inplace
    {
        char* buffer = static_cast<char*>(malloc(Size));
        if (buffer) {
            std::memcpy(buffer, Data, Size);
            doc.load_buffer_inplace(buffer, Size);
            free(buffer);
        }
    }

    // Test load_buffer_inplace_own
    {
        char* buffer = static_cast<char*>(malloc(Size));
        if (buffer) {
            std::memcpy(buffer, Data, Size);
            doc.load_buffer_inplace_own(buffer, Size);
        }
    }

    // Test load
    {
        std::stringstream stream;
        stream.write(reinterpret_cast<const char*>(Data), Size);
        doc.load(stream);
    }

    return 0;
}