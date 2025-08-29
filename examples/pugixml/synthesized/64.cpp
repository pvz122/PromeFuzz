// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load at pugixml.cpp:7694:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::save at pugixml.cpp:7767:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;

    // Load from string
    std::string xml_string(reinterpret_cast<const char*>(Data), Size);
    doc.load_string(xml_string.c_str());

    // Load from file
    std::ofstream file("./dummy_file", std::ios::binary);
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();
    doc.load_file("./dummy_file");

    // Load from stream
    std::istringstream stream(xml_string);
    doc.load(stream);

    // Save to file
    doc.save_file("./dummy_file");

    // Save to stream
    std::ostringstream out_stream;
    pugi::xml_writer_stream writer(out_stream);
    doc.save(writer);

    return 0;
}