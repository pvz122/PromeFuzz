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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    {
        char* str = new char[Size + 1];
        std::memcpy(str, Data, Size);
        str[Size] = '\0';
        doc.load_string(str);
        delete[] str;
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
        void* buffer = malloc(Size);
        std::memcpy(buffer, Data, Size);
        doc.load_buffer_inplace(buffer, Size);
        free(buffer);
    }

    // Test load_buffer_inplace_own
    {
        void* buffer = pugi::get_memory_allocation_function()(Size);
        std::memcpy(buffer, Data, Size);
        doc.load_buffer_inplace_own(buffer, Size);
    }

    // Test load
    {
        std::istringstream stream(std::string(reinterpret_cast<const char*>(Data), Size));
        doc.load(stream);
    }

    return 0;
}