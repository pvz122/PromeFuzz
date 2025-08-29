// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_parse_result::description at pugixml.cpp:7427:45 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_parse_result::description at pugixml.cpp:7427:45 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace at pugixml.cpp:7753:46 in pugixml.hpp
// pugi::xml_parse_result::description at pugixml.cpp:7427:45 in pugixml.hpp
// pugi::get_memory_allocation_function at pugixml.cpp:7870:52 in pugixml.hpp
// pugi::xml_document::load_buffer_inplace_own at pugixml.cpp:7760:46 in pugixml.hpp
// pugi::xml_parse_result::description at pugixml.cpp:7427:45 in pugixml.hpp
// pugi::xpath_parse_result::description at pugixml.cpp:12919:47 in pugixml.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a null-terminated copy of the input data
    char* buffer = new char[Size + 1];
    std::memcpy(buffer, Data, Size);
    buffer[Size] = '\0';

    // Test pugi::xml_document::load_string
    pugi::xml_document doc1;
    pugi::xml_parse_result result1 = doc1.load_string(buffer);
    const char* desc1 = result1.description();

    // Test pugi::xml_document::load_file
    FILE* file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
    pugi::xml_document doc2;
    pugi::xml_parse_result result2 = doc2.load_file("./dummy_file");
    const char* desc2 = result2.description();

    // Test pugi::xml_document::load_buffer_inplace
    pugi::xml_document doc3;
    char* inplace_buffer = new char[Size];
    std::memcpy(inplace_buffer, Data, Size);
    pugi::xml_parse_result result3 = doc3.load_buffer_inplace(inplace_buffer, Size);
    const char* desc3 = result3.description();
    delete[] inplace_buffer;

    // Test pugi::xml_document::load_buffer_inplace_own
    pugi::xml_document doc4;
    char* inplace_own_buffer = static_cast<char*>(pugi::get_memory_allocation_function()(Size));
    std::memcpy(inplace_own_buffer, Data, Size);
    pugi::xml_parse_result result4 = doc4.load_buffer_inplace_own(inplace_own_buffer, Size);
    const char* desc4 = result4.description();

    // Test pugi::xpath_parse_result::description
    pugi::xpath_parse_result xpath_result;
    const char* xpath_desc = xpath_result.description();

    delete[] buffer;
    return 0;
}