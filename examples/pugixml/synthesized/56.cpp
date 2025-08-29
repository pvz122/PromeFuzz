// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7819:34 in pugixml.hpp
// pugi::xml_document::save at pugixml.cpp:7767:34 in pugixml.hpp
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
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;

    // Load from string
    std::string xml_string(reinterpret_cast<const char*>(Data), Size);
    doc.load_string(xml_string.c_str());

    // Load from file
    std::ofstream outfile("./dummy_file");
    outfile.write(xml_string.c_str(), xml_string.size());
    outfile.close();
    doc.load_file("./dummy_file");

    // Save to file
    doc.save_file("./dummy_file");
    doc.save_file(L"./dummy_file");

    // Save to stream
    std::ostringstream oss;
    pugi::xml_writer_stream writer(oss);
    doc.save(writer);

    // Load from stream
    std::istringstream iss(xml_string);
    doc.load(iss);

    return 0;
}