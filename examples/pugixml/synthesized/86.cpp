// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7819:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::print at pugixml.cpp:6843:30 in pugixml.hpp
// pugi::xml_document::save at pugixml.cpp:7767:34 in pugixml.hpp
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
#include <fstream>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Load from buffer
    doc.load_buffer(Data, Size);

    // Save to file
    doc.save_file("./dummy_file");

    // Save to file with wchar_t path
    doc.save_file(L"./dummy_file");

    // Create a writer for print and save functions
    std::ostringstream oss;
    pugi::xml_writer_stream writer(oss);

    // Print the document
    if (doc.first_child()) {
        doc.first_child().print(writer);
    }

    // Save the document
    doc.save(writer);

    // Load from file
    doc.load_file("./dummy_file");

    return 0;
}