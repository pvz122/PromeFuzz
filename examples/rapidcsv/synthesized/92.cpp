// This fuzz driver is generated for library rapidcsv, aiming to fuzz the following functions:
// rapidcsv::Document::Load at rapidcsv.h:549:10 in rapidcsv.h
// rapidcsv::Document::Save at rapidcsv.h:569:10 in rapidcsv.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include "rapidcsv.h"

extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file to work with
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) return 0;

    // Write the fuzz data to the dummy file
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    try {
        // Initialize parameters for Document
        rapidcsv::LabelParams labelParams{0};
        rapidcsv::SeparatorParams separatorParams{',', true};
        rapidcsv::ConverterParams converterParams{true, 0.0, 0};
        rapidcsv::LineReaderParams lineReaderParams{true, '#'};

        // Load the document from the dummy file
        rapidcsv::Document doc("./dummy_file", labelParams, separatorParams, converterParams, lineReaderParams);
        
        // Save the document to a new path
        doc.Save("./saved_file.csv");

        // Load the document again using the stream
        std::ifstream inputStream("./dummy_file");
        if (inputStream.is_open()) {
            doc.Load(inputStream, labelParams, separatorParams, converterParams, lineReaderParams);
            inputStream.close();
        }

    } catch (...) {
        // Catch any exceptions thrown by rapidcsv
    }

    return 0;
}