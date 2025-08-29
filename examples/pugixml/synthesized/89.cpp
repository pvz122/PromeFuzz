// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_document::load_file at pugixml.cpp:7726:46 in pugixml.hpp
// pugi::xml_document::load at pugixml.cpp:7694:46 in pugixml.hpp
// pugi::xml_document::save_file at pugixml.cpp:7811:34 in pugixml.hpp
// pugi::xml_document::save at pugixml.cpp:7767:34 in pugixml.hpp
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
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;

    // Create a null-terminated copy of the input data for load_string
    std::string xmlString(reinterpret_cast<const char*>(Data), Size);

    // Test load_string
    doc.load_string(xmlString.c_str());

    // Test load_file
    std::ofstream outFile("./dummy_file");
    outFile.write(xmlString.c_str(), xmlString.size());
    outFile.close();
    doc.load_file("./dummy_file");

    // Test load with istream
    std::istringstream iss(xmlString);
    doc.load(iss);

    // Test save_file
    doc.save_file("./dummy_file");

    // Test save with ostream
    std::ostringstream oss;
    pugi::xml_writer_stream writer(oss);
    doc.save(writer);

    // Test load with deprecated load(const char_t*, unsigned int)
    doc.load(xmlString.c_str());

    return 0;
}