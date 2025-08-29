// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::reset at pugixml.cpp:7487:34 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::get_memory_allocation_function at pugixml.cpp:7870:52 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace_own at pugixml.cpp:7760:46 in pugixml.hpp
// pugi::xml_document::load at pugixml.cpp:7721:46 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Test load_string
    {
        char* null_terminated_data = new char[Size + 1];
        std::copy(Data, Data + Size, null_terminated_data);
        null_terminated_data[Size] = '\0';
        doc.load_string(null_terminated_data);
        delete[] null_terminated_data;
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
        char* buffer = new char[Size];
        std::copy(Data, Data + Size, buffer);
        doc.load_buffer_inplace(buffer, Size);
        delete[] buffer;
    }

    // Test load_buffer_inplace_own
    {
        void* buffer = pugi::get_memory_allocation_function()(Size);
        std::copy(Data, Data + Size, reinterpret_cast<char*>(buffer));
        doc.load_buffer_inplace_own(buffer, Size);
    }

    // Test load
    {
        char* null_terminated_data = new char[Size + 1];
        std::copy(Data, Data + Size, null_terminated_data);
        null_terminated_data[Size] = '\0';
        doc.load(null_terminated_data);
        delete[] null_terminated_data;
    }

    return 0;
}