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
#include <pugixml.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Randomly choose which function to test
    int choice = rand() % 6;

    switch (choice) {
        case 0: {
            // load_string
            char* str = new char[Size + 1];
            memcpy(str, Data, Size);
            str[Size] = '\0';
            doc.load_string(str);
            delete[] str;
            break;
        }
        case 1: {
            // load_buffer_inplace
            char* buffer = new char[Size];
            memcpy(buffer, Data, Size);
            doc.load_buffer_inplace(buffer, Size);
            delete[] buffer;
            break;
        }
        case 2: {
            // load_buffer
            doc.load_buffer(Data, Size);
            break;
        }
        case 3: {
            // load
            std::istringstream stream(std::string(reinterpret_cast<const char*>(Data), Size));
            doc.load(stream);
            break;
        }
        case 4: {
            // load_buffer_inplace_own
            char* buffer = static_cast<char*>(malloc(Size));
            memcpy(buffer, Data, Size);
            doc.load_buffer_inplace_own(buffer, Size);
            break;
        }
        case 5: {
            // load_file
            std::ofstream outfile("./dummy_file", std::ios::binary);
            outfile.write(reinterpret_cast<const char*>(Data), Size);
            outfile.close();
            doc.load_file("./dummy_file");
            break;
        }
        default:
            break;
    }

    return 0;
}