// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7819:34 in pugixml.hpp
// pugi::xml_node::print at pugixml.cpp:6862:30 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::save at pugixml.cpp:7803:34 in pugixml.hpp
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
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;

    // Load from buffer
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    // Save to file (char* overload)
    doc.save_file("./dummy_file");

    // Save to file (wchar_t* overload)
    doc.save_file(L"./dummy_file");

    // Print to wstring stream
    std::wstringstream wss;
    doc.print(wss);

    // Load from file
    pugi::xml_parse_result file_result = doc.load_file("./dummy_file");
    if (!file_result) return 0;

    // Save to wstring stream
    doc.save(wss);

    return 0;
}